from flask import Flask , render_template , url_for , redirect , request , jsonify
import os.path
import json
import time
import serial


port = '/dev/ttyS2'

arduino = serial.Serial(port, baudrate = 9600 , timeout = 1)


app = Flask(__name__)

@app.route('/')
def root():
    if os.path.exists('length.json'):
        return redirect(url_for('welcome'))
    else:
        return redirect(url_for('length'))
@app.route('/Welcome' , methods= ['GET' , 'POST'])
def welcome():
    if request.method == 'GET':
        return render_template('index.html')
    else:
        lengthDict ={'length' : request.form['length']}
        with open('length.json' , 'w') as lengthFile:
            json.dump(lengthDict , lengthFile)
            lengthSerialPort = lengthDict['length'] * 1.5
            arduino.write(lengthSerialPort)
            return render_template('index.html')
@app.route('/length')
def length():
    return render_template('length.html')
        
@app.route('/_scadule' , methods= ['POST'])
def timeGetting():
    openTime = request.form['openTime']
    closeTime = request.form['closeTime']
    print(type(openTime))
    schedule = {'openTime' : openTime, 'closeTime' : closeTime}
    with open('schedule.json' , 'w') as scheduleFile:
        json.dump(schedule , scheduleFile)
    return jsonify({'openTime':openTime})
    
@app.route('/_positionGet' , methods = ['GET' , 'POST'])
def position_get():
    desiredPosition = request.args.get('position' , type = int)
    print(desiredPosition)
    arduino.write(desiredPosition)
    return jsonify(position = desiredPosition)
@app.route('/_auto' , methods= ['GET' , 'POST'])
def auto_mode():
    state = request.get_json()
    autoCode = state['state']
    print(autoCode)
    arduino.write(autoCode)
    return jsonify(code = autoCode)
    

if __name__ == '__main__' :
    app.run(host= '0.0.0.0' )
