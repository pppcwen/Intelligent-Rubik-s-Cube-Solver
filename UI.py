import tkinter as tk
from tkinter import ttk
import threading

# Define the color sequence used for switching
color_order = ["white", "yellow", "blue", "green", "red", "orange"]

# Initial colors for each face of the cube
initial_colors = {
    "U": [["yellow"] * 3 for _ in range(3)],  # Up
    "L": [["red"] * 3 for _ in range(3)],   # Left
    "F": [["green"] * 3 for _ in range(3)],    # Front
    "R": [["orange"] * 3 for _ in range(3)],  # Right
    "B": [["blue"] * 3 for _ in range(3)], # Back
    "D": [["white"] * 3 for _ in range(3)], # Down
}

# Position and order of the unfolded cube
faces = {
    "U": (0, 1),  # Up
    "L": (1, 0),  # Left
    "F": (1, 1),  # Front
    "R": (1, 2),  # Right
    "B": (1, 3),  # Back
    "D": (2, 1),  # Down
}

global_front=""
global_back=""
global_left=""
global_right=""
global_up=""
global_down=""
global_cube_state = ""

class CubeApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Magic Cube")
        self.root.configure(bg="#f5f5f5")
        
        # Main frame for the canvas
        self.main_frame = tk.Frame(root, bg="#f5f5f5")
        self.main_frame.pack(side=tk.LEFT, padx=20, pady=20)

        # Canvas for drawing the cube
        self.canvas = tk.Canvas(self.main_frame, width=700, height=500, bg="#d9d9d9", bd=0, highlightthickness=0)
        self.canvas.pack()

        # Control panel on the right
        self.control_panel = tk.Frame(root, bg="#f5f5f5", width=200)
        self.control_panel.pack(side=tk.RIGHT, fill=tk.Y, padx=10, pady=10)

        # Offset for centering the cube
        self.offset_x = 50  # Horizontal offset
        self.offset_y = 25   # Vertical offset

        # Size of each square
        self.size = 50
        # Store the current color state of the cube
        self.colors = {face: [row[:] for row in grid] for face, grid in initial_colors.items()}

        # Draw the initial unfolded cube
        self.draw_cube()

        # Add title in the control panel
        self.title_label = tk.Label(self.control_panel, text="Cube Controller", bg="#f5f5f5", fg="black", font=("Arial", 16, "bold"))
        self.title_label.pack(pady=10)

        # Add a button to save the cube state
        self.save_button = ttk.Button(self.control_panel, text="Save Cube State", command=self.save_cube_state)
        self.save_button.pack(pady=20)

        # Add a label to show the validation status
        self.state_label = tk.Label(self.control_panel, text="Status: Waiting", bg="#f5f5f5", fg="black", font=("Arial", 12, "bold"))
        self.state_label.pack(pady=10)

        # Add separator
        self.separator = ttk.Separator(self.control_panel, orient="horizontal")
        self.separator.pack(fill=tk.X, pady=10)

        # Add info panel for cube states
        self.info_label = tk.Label(self.control_panel, text="Cube State Info", bg="#f5f5f5", fg="black", font=("Arial", 14, "bold"))
        self.info_label.pack(pady=10)

        self.state_text = tk.Text(self.control_panel, height=10, width=25, bg="#ffffff", fg="black", font=("Courier", 10), wrap=tk.WORD, state=tk.DISABLED)
        self.state_text.pack(pady=10)

    def draw_face(self, face, top_left_x, top_left_y):
        """Draw a single face of the 3x3 grid and make it clickable."""
        for row in range(3):
            for col in range(3):
                x0 = top_left_x + col * self.size + self.offset_x
                y0 = top_left_y + row * self.size + self.offset_y
                x1 = x0 + self.size
                y1 = y0 + self.size

                # Get the current color of the cell
                color = self.colors[face][row][col]

                # Draw the rectangle with black border
                rect = self.canvas.create_rectangle(
                    x0, y0, x1, y1, fill=color, outline="black", width=2
                )

                # Use lambda to correctly bind coordinates and face information
                self.canvas.tag_bind(
                    rect, "<Button-1>",
                    lambda event, f=face, r=row, c=col: self.change_color(f, r, c)
                )

    def draw_cube(self):
        """Draw the entire unfolded view of the cube."""
        for face, (row, col) in faces.items():
            self.draw_face(
                face,
                col * self.size * 3,  # Horizontal position
                row * self.size * 3   # Vertical position
            )

    def update_face(self, face):
        """Redraw all cells of the specified face."""
        row, col = faces[face]
        top_left_x = col * self.size * 3
        top_left_y = row * self.size * 3
        self.draw_face(face, top_left_x, top_left_y)


    def change_color(self, face, row, col):
        """Switch the color of the specified cell."""
        # Get the current color
        current_color = self.colors[face][row][col]
        # Find the next color in the sequence
        next_color = color_order[(color_order.index(current_color) + 1) % len(color_order)]
        # Update the color
        self.colors[face][row][col] = next_color

        # Redraw the updated cell
        self.update_face(face)



    def save_cube_state(self):
        """Save the current state of the cube."""
        state = {}
        # Map colors to abbreviations
        color_map = {
            "white": "W",
            "yellow": "Y",
            "blue": "B",
            "green": "G",
            "red": "R",
            "orange": "O",
        }
        color_counts = {color: 0 for color in color_map.values()}

        for face in self.colors:
            # Flatten the 3x3 grid into a single string
            face_state = "".join(color_map[self.colors[face][r][c]] for r in range(3) for c in range(3))
            state[face] = face_state
            # Count the colors
            for char in face_state:
                color_counts[char] += 1

        # Validate the state
        if all(count == 9 for count in color_counts.values()):
            self.saved_state = state  # Store the valid state
            self.state_label.config(text="Status: Valid", fg="#27ae60")
            self.update_state_display(state)

            # Store the valid state in global variables
            global global_front 
            global_front = state["F"]
            global global_back 
            global_back= state["B"]
            global global_left 
            global_left= state["L"]
            global global_right 
            global_right= state["R"]
            global global_up 
            global_up= state["U"]
            global global_down 
            global_down= state["D"]
            global global_cube_state 
            global_cube_state= global_up+global_right+global_front+global_down+global_left+global_back
        else:
            self.state_label.config(text="Status: Invalid", fg="#e74c3c")
            self.update_state_display({"Error": "Invalid state. Ensure each color appears exactly 9 times."})

    def update_state_display(self, state):
        """Update the cube state display in the text box."""
        self.state_text.config(state=tk.NORMAL)
        self.state_text.delete(1.0, tk.END)
        for key, value in state.items():
            self.state_text.insert(tk.END, f"{key}: {value}\n")
        self.state_text.config(state=tk.DISABLED)

def get_cube_state():
    return global_cube_state

# Start the application
# if __name__ == "__main__":
#     root = tk.Tk()
#     app = CubeApp(root)
#     root.mainloop()
