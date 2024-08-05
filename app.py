import serial
import threading
from flask import Flask, jsonify, render_template

# Initialize global variable
parking_status = "No car is Parked"

def read_from_arduino():
    global parking_status
    arduino = serial.Serial('COM3', 9600, timeout=1)
    while True:
        line = arduino.readline().decode('utf-8').strip()
        if line == "Car is Parked":
            parking_status = line
        elif line == "No car is Parked":
            parking_status = line

# Start a thread to read data from Arduino
thread = threading.Thread(target=read_from_arduino)
thread.daemon = True
thread.start()

app = Flask(__name__)

@app.route('/status')
def get_parking_status():
    global parking_status
    return jsonify({'status': parking_status})

@app.route('/')
def index():
    return render_template('template.html')

if __name__ == '__main__':
    app.run(debug=True)
