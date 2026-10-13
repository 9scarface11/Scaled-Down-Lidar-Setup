import serial
import csv

# Apna port yahan update karo
arduino_port = 'COM7' 
baud_rate = 115200

ser = serial.Serial(arduino_port, baud_rate)

with open('servo_tof_data_3d.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    # Header mein ab dono angles likhenge
    writer.writerow(["v_drift","h_drift","Angle1", "Angle2", "Distance_mm"]) 
    
    print("Data record hona shuru ho gaya hai... (Rukne ke liye Ctrl+C dabayein)")
    
    while True:
        try:
            # Arduino se aayi hui puri line read karo (jaise "45,90,125")
            line = ser.readline().decode('utf-8').strip()
            
            # Agar line mein 2 commas hain, toh usko 3 hisso mein split karo
            if line.count(',') == 2:
                angle1, angle2, distance = line.split(',') 
                writer.writerow([angle1, angle2, distance])
                print(f"Angle1: {angle1}° | Angle2: {angle2}° | Distance: {distance}mm")
                
        except KeyboardInterrupt:
            print("\nData collection ruk gaya hai. File save ho gayi.")
            break