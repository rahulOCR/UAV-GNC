
# ##############################################################################################

import math
import matplotlib.pyplot as plt

# Haversine and simple lat/lon → NED conversion (flat earth approximation)
def latlon_to_ned(lat0, lon0, lat, lon):
    R = 6371000  # Earth radius in meters
    dlat = math.radians(lat - lat0)
    dlon = math.radians(lon - lon0)
    north = dlat * R
    east = dlon * R * math.cos(math.radians(lat0))
    return east, north

# Inverse: NED back to lat/lon
def ned_to_latlon(lat0, lon0, east, north):
    R = 6371000
    dlat = north / R
    dlon = east / (R * math.cos(math.radians(lat0)))
    return lat0 + math.degrees(dlat), lon0 + math.degrees(dlon)

# L1 controller with GPS input
def l1_controller_gps(current_latlon, wp1_latlon, wp2_latlon, ground_speed, L1_dist, max_roll_deg=35):
    cx, cy = latlon_to_ned(wp1_latlon[0], wp1_latlon[1], current_latlon[0], current_latlon[1])
    x1, y1 = 0, 0
    x2, y2 = latlon_to_ned(wp1_latlon[0], wp1_latlon[1], wp2_latlon[0], wp2_latlon[1])

    dx = x2 - x1
    dy = y2 - y1
    path_length = math.hypot(dx, dy)
    dx /= path_length
    dy /= path_length

    rx = cx - x1
    ry = cy - y1
    cross_track = rx * dy - ry * dx
    eta = math.atan2(cross_track, L1_dist)
    a_lat = 2 * ground_speed**2 / L1_dist * math.sin(eta)
    phi_des = math.atan2(a_lat, 9.81)
    phi_des_deg = math.degrees(phi_des)
    phi_des_deg = max(-max_roll_deg, min(max_roll_deg, phi_des_deg))

    return phi_des_deg, cross_track

# # Reference path: 2 GPS waypoints (a straight east path)
# wp1_latlon = (28.6139, 77.2090)        # Start waypoint (Delhi center)
# wp2_latlon = (28.6139, 77.2190)        # End waypoint (about 1km east)

# # Simulate aircraft coming from north of the path
# positions = [(28.6149 - 0.0001*i, 77.2140) for i in range(15)]  # Heading south

# # Run controller
# roll_commands = []
# cross_tracks = []

# for pos in positions:
#     roll, cte = l1_controller_gps(pos, wp1_latlon, wp2_latlon, ground_speed=25.0, L1_dist=20.0)
#     roll_commands.append(roll)
#     cross_tracks.append(cte)

# # Plot results
# fig, ax1 = plt.subplots(figsize=(10, 5))

# color = 'tab:red'
# ax1.set_xlabel('Position Index (approaching path)')
# ax1.set_ylabel('Roll Command (deg)', color=color)
# ax1.plot(range(len(positions)), roll_commands, 'o-', color=color)
# ax1.tick_params(axis='y', labelcolor=color)
# ax1.grid(True)

# ax2 = ax1.twinx()
# color = 'tab:blue'
# ax2.set_ylabel('Cross Track Error (m)', color=color)
# ax2.plot(range(len(positions)), cross_tracks, 'x--', color=color)
# ax2.tick_params(axis='y', labelcolor=color)

# plt.title("L1 Controller with GPS: Roll Command vs Cross-Track Error")
# plt.tight_layout()
# plt.show()



# ########################################################################################################


# Simulate aircraft trajectory with L1 controller using GPS positions and simple dynamics

# Reference path (straight line)










wp1_latlon = (28.6139, 77.2090)
wp2_latlon = (28.6139, 77.2190)

# Initial aircraft position (north of path)
lat, lon = 28.6170, 77.2140
heading_deg = -90  # heading south
ground_speed = 25.0  # m/s
L1_dist = 20.0
dt = 0.5  # time step (s)
steps = 60

# Storage for trajectory
trajectory_latlon = [(lat, lon)]
roll_commands = []

for _ in range(steps):
    # Run L1 controller
    roll_deg, _ = l1_controller_gps((lat, lon), wp1_latlon, wp2_latlon, ground_speed, L1_dist)
    roll_commands.append(roll_deg)

    # Convert roll to turn rate (approximate coordinated turn)
    phi_rad = math.radians(roll_deg)
    turn_radius = ground_speed**2 / (9.81 * math.tan(phi_rad)) if abs(roll_deg) > 1e-2 else 1e6
    omega = ground_speed / turn_radius  # rad/s
    heading_rad = math.radians(heading_deg)
    heading_rad += omega * dt
    heading_deg = math.degrees(heading_rad)

    # Update position using heading and speed
    dx = ground_speed * math.cos(heading_rad) * dt
    dy = ground_speed * math.sin(heading_rad) * dt
    east, north = latlon_to_ned(wp1_latlon[0], wp1_latlon[1], lat, lon)
    east += dx
    north += dy
    lat, lon = ned_to_latlon(wp1_latlon[0], wp1_latlon[1], east, north)

    trajectory_latlon.append((lat, lon))

# Convert trajectory to NED for plotting
trajectory_ned = [latlon_to_ned(wp1_latlon[0], wp1_latlon[1], lt, ln) for lt, ln in trajectory_latlon]
wp_start_ned = (0, 0)
wp_end_ned = latlon_to_ned(wp1_latlon[0], wp1_latlon[1], wp2_latlon[0], wp2_latlon[1])

# Plot the 2D path
x_vals, y_vals = zip(*trajectory_ned)
plt.figure(figsize=(10, 6))
plt.plot(x_vals, y_vals, label='Aircraft Path', color='blue', marker='.')
plt.plot([wp_start_ned[0], wp_end_ned[0]], [wp_start_ned[1], wp_end_ned[1]], 'r--', label='Reference Path')
plt.xlabel('East (m)')
plt.ylabel('North (m)')
plt.title('L1 Controller: Aircraft Trajectory vs Reference Path')
plt.legend()
plt.grid(True)
plt.axis('equal')
plt.tight_layout()
plt.show()

