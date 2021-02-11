import RPi.GPIO as GPIO
import time


# Pin Definitons:
pwm_pin = 18 # Broadcom pin 18 (P1 pin 12)
led_pin = 23 # Broadcom pin 23 (P1 pin 16)
button_pin = 17 # Broadcom pin 17 (P1 pin 11)

# GPIO.setmode(GPIO.BCM)
# GPIO.setwarnings(False)
# GPIO.setup(12, GPIO.OUT)

dc = 95 # Duty cycle (0 - 100) for PWM pin

# Pin Setup:
GPIO.setmode(GPIO.BCM) # Broadcom pin-numbering scheme
GPIO.setup(led_pin, GPIO.OUT) # LED pin set as output
GPIO.setup(pwm_pin, GPIO.OUT) # PWM pin set as output
pwm = GPIO.PWM(pwm_pin, 50)  # Initialize PWM on pwmPin 100Hz frequency
GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP) # Button pin set as 
                                                          # input w/ pull-up

# Initial state for LEDs:
GPIO.output(led_pin, GPIO.LOW)
pwm.start(dc)

print("Here we go! Press CTRL+C to exit")
try:
    while True:
        print("LED on")
        GPIO.output(led_pin, GPIO.HIGH)
        time.sleep(1)
        print("LED off")
        GPIO.output(led_pin, GPIO.LOW)
        time.sleep(1)
except KeyboardInterrupt: # If CTRL+C is pressed, exit cleanly:
    GPIO.cleanup() # Clean up all GPIO
