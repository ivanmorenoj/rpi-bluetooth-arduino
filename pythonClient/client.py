import time
import serial

ser = serial.Serial(
    port='/dev/rfcomm0',
    baudrate=115200,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

ser.isOpen()

print('Enter your message below.\r\nInsert "exit" to leave the application.')

while 1 :
    user_input = input("You message >> ")
    if user_input == 'exit':
        ser.close()
        exit()
    else:
        user_input = user_input + '\r'
        ser.write(user_input.encode())
        recv = ''
        tic = time.time()
        while time.time() - tic < 15 and ser.inWaiting() == 0: 
            time.sleep(1)

        if ser.inWaiting() > 0:
            recv = ser.readline()

        if recv != '':
            print("Server Response >> " + str(recv, 'utf-8'))
