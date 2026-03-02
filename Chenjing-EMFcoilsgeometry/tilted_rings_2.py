import numpy as np

# Define tilt angles
tilt_theta = 56. * np.pi / 180.
tilt_phi = -54. * np.pi / 180.

# Input data
zc = np.fromstring("""
        21.271,  20.602,  19.554,  18.555,
        17.077,  15.600,  14.122,  12.644,
        11.166,   9.685,   8.207,   6.729,
         5.251,   3.773,   2.295,   0.817,
        -0.821,  -2.299,  -3.777,  -5.255,
        -6.733,  -8.210,  -9.688, -11.166,
       -12.644, -14.122, -15.600, -17.077,
       -18.555, -19.554, -20.602, -21.271
        """, sep="," )

rc = np.fromstring("""
        3.843,   6.509,   9.185,  11.053,
       13.210,  14.924,  16.325,  17.495,
       18.465,  19.282,  19.951,  20.502,
       20.930,  21.240,  21.450,  21.559,
       21.559,  21.450,  21.240,  20.930,
       20.502,  19.951,  19.282,  18.465,
       17.495,  16.325,  14.924,  13.210,
       11.053,   9.185,   6.509,   3.843
       """, sep="," )

# Number of points per ring
n_points_per_ring = 36

# Create rotation matrix to align z-axis with tilt axis
R_y = np.array([
    [np.cos(tilt_theta), 0, np.sin(tilt_theta)],
    [0, 1, 0],
    [-np.sin(tilt_theta), 0, np.cos(tilt_theta)]
])

R_z = np.array([
    [np.cos(tilt_phi), -np.sin(tilt_phi), 0],
    [np.sin(tilt_phi), np.cos(tilt_phi), 0],
    [0, 0, 1]
])

R = R_z @ R_y

# Sphere radius (assuming points lie on a sphere)
# We can estimate from the data - using the magnitude of the furthest point
sphere_radius = np.sqrt(zc[0]**2 + rc[0]**2)  # ~21.5 based on first point

# Generate the flight path data
flight_paths = []

for i in range(len(zc)):
    # Generate angles for this ring
    angles = np.linspace(0, 2*np.pi, n_points_per_ring, endpoint=False)
    
    for angle in angles:
        # 1. EYE position (on the ring)
        # Until coordinates
        eye_untilted = np.array([
            rc[i] * np.cos(angle),
            rc[i] * np.sin(angle),
            zc[i]
        ])
        
        # Apply tilt
        eye = R @ eye_untilted
        
        # 2. LOOK position (point on sphere surface along radial direction)
        # The sphere center is at origin
        # Look direction is from eye position toward sphere center
        look_dir = -eye / np.linalg.norm(eye)
        look = look_dir * sphere_radius * 0.95  # Slightly inside the sphere
        
        # Alternative: Look at the origin directly
        # look = np.array([0.0, 0.0, 0.0])
        
        # 3. UP direction (perpendicular to view direction and ring tangent)
        # First, get the tangent direction along the ring (derivative of position wrt angle)
        tangent_untilted = np.array([
            -rc[i] * np.sin(angle),
            rc[i] * np.cos(angle),
            0
        ])
        tangent = R @ tangent_untilted
        tangent = tangent / np.linalg.norm(tangent)
        
        # View direction (from eye to look)
        view_dir = look - eye
        view_dir = view_dir / np.linalg.norm(view_dir)
        
        # Up direction should be perpendicular to view_dir and tangent
        # and point roughly outward from sphere
        up = np.cross(view_dir, tangent)
        up = up / np.linalg.norm(up)
        
        # Ensure up points away from sphere center (roughly)
        if np.dot(up, eye) < 0:
            up = -up
        
        # Create the 4x4 block for this position
        block = np.array([
            [eye[0], eye[1], eye[2], 1],  # Eye position
            [look[0], look[1], look[2], 1],  # Look position
            [up[0], up[1], up[2], 0],  # Up direction
            [0, 0, 0, 0]  # Padding row
        ])
        
        flight_paths.append(block)

# Convert to single numpy array
flight_paths = np.array(flight_paths)

print(f"Flight path data shape: {flight_paths.shape}")
print(f"Number of positions: {len(flight_paths)}")
print(f"Each block is 4x4: {flight_paths[0].shape}")
print("\nFirst block:")
print(flight_paths[0])

# Example: access specific elements
print("\nFirst eye position:", flight_paths[0][0, :3])
print("First look position:", flight_paths[0][1, :3])
print("First up direction:", flight_paths[0][2, :3])


if 0:

    # Alternative approach with consistent up direction (always pointing north/top)
    flight_paths_north_up = []

    # Define a reference up direction in untilted coordinates
    # For north-up, we want up to point in the direction of the tilt axis
    tilt_axis_untilted = np.array([0, 0, 1])
    tilt_axis = R @ tilt_axis_untilted

    for i in range(len(zc)):
        angles = np.linspace(0, 2*np.pi, n_points_per_ring, endpoint=False)
        
        for angle in angles:
            # Eye position (same as before)
            eye_untilted = np.array([
                rc[i] * np.cos(angle),
                rc[i] * np.sin(angle),
                zc[i]
            ])
            eye = R @ eye_untilted
            
            # Look at origin
            look = np.array([0.0, 0.0, 0.0])
            
            # View direction
            view_dir = look - eye
            view_dir = view_dir / np.linalg.norm(view_dir)
            
            # Make up direction perpendicular to view_dir and the tilt axis
            up = np.cross(view_dir, tilt_axis)
            up = up / np.linalg.norm(up)
            
            # Ensure up points roughly in the same hemisphere as tilt_axis
            if np.dot(up, tilt_axis) < 0:
                up = -up
            
            block = np.array([
                [eye[0], eye[1], eye[2], 1],
                [look[0], look[1], look[2], 1],
                [up[0], up[1], up[2], 0],
                [0, 0, 0, 0]
            ])
            
            flight_paths_north_up.append(block)

    flight_paths_north_up = np.array(flight_paths_north_up)

    print("\n" + "="*50)
    print("Alternative with consistent up direction (along tilt axis):")
    print(f"Tilt axis: {tilt_axis}")
    print("\nFirst block with north-up:")
    print(flight_paths_north_up[0])

    # If you need to save the data for the renderer
    # np.save('flight_paths.npy', flight_paths)
    # np.save('flight_paths_north_up.npy', flight_paths_north_up)

    # Or save as text for inspection
    # np.savetxt('flight_paths_first_block.txt', flight_paths[0], fmt='%.6f')
