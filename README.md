# Traffic Light Controller

This project is an Arduino-based traffic light controller using an ATmega328P microcontroller. It uses Timer1 to handle the traffic light state changes and pin toggling.

## Features

- Four states: Red, Red and Yellow, Green, Yellow
- Adjustable duration for each state
- Interrupt-driven state changes

## Pin Configuration

- Red LED: Pin 11 (PB3)
- Yellow LED: Pin 12 (PB4)
- Green LED: Pin 13 (PB5)

## Dependencies

- avr-gcc compiler
- avr-libc library

## Usage

1. Clone this repository:
<pre>
git clone https://github.com/yourusername/traffic-light-controller.git
</pre>

2. Open the project folder and compile the source code:
<pre>
cd traffic-light-controller
make
</pre>
3. Upload the compiled binary to your ATmega328P microcontroller using an ISP programmer:
<pre>
make upload
</pre>


4. The traffic light controller should now be running on your microcontroller.

## Customization

You can adjust the duration of each state by modifying the following definitions in the `main.cpp` file:

- `RED_ONLY_DURATION`
- `RED_AND_YELLOW_DURATION`
- `GREEN_ONLY_DURATION`
- `YELLOW_ONLY_DURATION`

## License

This project is released under the [MIT License](LICENSE).

