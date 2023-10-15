import serial
from serial import Serial
from pynput.mouse import Button, Controller

mouse = Controller()
try:
    com_port = input("Enter the COM port (e.g., COM7): ")
    ser = serial.Serial(com_port, baudrate=115200)  # Setting Serial port number and baudrate
    while True:  # While loop to continuously scan and read data from the serial port and execute
        dump = ser.readline()  # Reading Serial port
        dump = str(dump)  # Converting byte data into a string
        dump = dump[2:-5]  # Cleaning up the raw data received from the serial port
        data = dump.split(',')  # Splitting up the data into individual items in a list, with the first item being the data identifier
        print(data)
        if data[0] == "DATAL":  # Checking if the identifier is "DATAL," which the Arduino sends as the gyro X, Y, and Z values
            mouse.move(int(data[1]), int(data[2]))  # Moving the mouse by using the X and Y values after converting them into integers

        if data[0] == "DATAB":  # Checking if the identifier is "DATAB," which the Arduino sends the values for Left/Right button
            if data[1] == 'L':  # If the Left button is pressed
                mouse.press(Button.left)  # The corresponding button is pressed and released
                mouse.release(Button.left)
            if data[1] == 'R':  # If the Right button is pressed
                mouse.press(Button.right)  # The corresponding button is pressed and released
                mouse.release(Button.right)
except Exception as e:
    print(f"An error occurred: {str(e)}")
    k = input("Press any key to exit.")
