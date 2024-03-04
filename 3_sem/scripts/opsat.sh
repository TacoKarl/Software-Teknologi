# Buttons
echo 12 > /sys/class/gpio/export
echo 16 > /sys/class/gpio/export

# LED
echo 20 > /sys/class/gpio/export
echo 21 > /sys/class/gpio/export
echo 26 > /sys/class/gpio/export

# LED output
echo out > /sys/class/gpio/gpio20/direction
echo out > /sys/class/gpio/gpio21/direction
echo out > /sys/class/gpio/gpio26/direction

