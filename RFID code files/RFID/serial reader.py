import serial
import csv

arduino_port = "COM4" #serial port of Arduino
baud = 9600 #arduino uno runs at 9600 baud
fileName="data.csv" #name of the CSV file generated

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
print("Created file")


while True:
    getData=ser.readline()
    dataString = getData.decode('utf-8')
    data=dataString[0:][:-2]
    print(data)


    readings = data.split(",")


    with open(fileName, 'w', encoding='UTF8', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(readings)

    file.close()

