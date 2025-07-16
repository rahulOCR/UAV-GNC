import numpy as np
import matplotlib.pyplot as plt

# Earth radius not needed for flat 2D sim
def wrap_pi(angle):
    """Wrap angle to [-pi, pi]"""
    return (angle + np.pi) % (2 * np.pi) - np.pi

class L1Controller:
    def __init__(self, L1_dist):
        self.L1_dist = L1_dist

    def guidance(self, drone_pos, drone_heading, wp_from, wp_to):
        """
        L1 guidance angle computation.
        """
        dx = wp_to[0] - wp_from[0]
        dy = wp_to[1] - wp_from[1]
        path_angle = np.arctan2(dy, dx)

        dx_ap = drone_pos[0] - wp_from[0]
        dy_ap = drone_pos[1] - wp_from[1]
        distance_ap = np.hypot(dx_ap, dy_ap)

        course_angle_ap = np.arctan2(dy_ap, dx_ap)

        # Cross-track error
        xtk = distance_ap * np.sin(course_angle_ap - path_angle)

        # Along-track distance (projection)
        along_track = distance_ap * np.cos(course_angle_ap - path_angle)

        # L1 angle
        eta = np.arctan2(-xtk, self.L1_dist + along_track)

        # Turn command = desired heading change
        return wrap_pi(eta)

# Parameters
radius = 100
center = np.array([0.0, 0.0])
speed = 10.0
dt = 0.1
T = 150  # total time

# L1 controller
l1 = L1Controller(L1_dist=20.0)

# Initial drone state
drone_pos = np.array([radius, 0.0])
drone_heading = np.radians(90)  # facing +Y

# Data logging
path_x = []
path_y = []
circle_x = []
circle_y = []

# Simulate
for t in np.arange(0, T, dt):
    # Desired point on circle
    angle = t * speed / radius
    wp_to = center + radius * np.array([np.cos(angle), np.sin(angle)])
    wp_from = center + radius * np.array([np.cos(angle - 0.1), np.sin(angle - 0.1)])

    # Get L1 turn angle (heading error)
    eta = l1.guidance(drone_pos, drone_heading, wp_from, wp_to)

    # Apply turn (proportional control to heading)
    drone_heading += eta * 0.1  # damping factor

    # Update drone position
    drone_pos += speed * dt * np.array([np.cos(drone_heading), np.sin(drone_heading)])

    path_x.append(drone_pos[0])
    path_y.append(drone_pos[1])
    circle_x.append(wp_to[0])
    circle_y.append(wp_to[1])

# Plot
plt.figure(figsize=(7,7))
plt.plot(path_x, path_y, label='Drone Path', color='blue')
plt.plot(circle_x, circle_y, label='Reference Circle', color='red', linestyle='--')
plt.scatter([0], [0], color='black', label='Center')
plt.xlabel("X (m)")
plt.ylabel("Y (m)")
plt.title("L1 Controller - Circular Path Following")
plt.axis('equal')
plt.grid(True)
plt.legend()
plt.show()
