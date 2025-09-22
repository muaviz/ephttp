# ephttp

The **ep** in **ephttp** can stand for a lot of things. Originally it was short for *ez pz* (easy-peasy) HTTP server. But you could also imagine it being *eepy* HTTP, or *extremely pointless* HTTP, or whatever else your creativity allows. The name isn’t that deep — kind of like the project itself.

This project is **not** about reinventing Apache or Nginx. It’s a small experiment meant to demonstrate the use of **object-oriented programming concepts in C++**. HTTP just happened to be the playground because, well, parsing text and opening sockets is more fun than coding yet another “Bank Account” class.

## Features

- Tiny HTTP server written in C++17  
- Built around classes to show off OOP principles (encapsulation, abstraction, inheritance, polymorphism)  
- Default handler serves a simple “Hello World”-style page  
- No dependencies beyond the standard C++ library and basic socket APIs  

In short: it compiles, it runs, and it proves you can do OOP with something more interesting than geometric shapes.

## Installation

```bash
git clone <repo>
cd ephttp
make
./server
````

Then open [http://localhost:8080](http://localhost:8080) in your browser to see the default page.

## Usage

- The server starts on port **8080** by default.
- Edit the code if you want to change routes, responses, or port numbers. (This is a teaching/demo project, not a production framework, so you’re encouraged to poke around and break things.)

## Requirements

- A C++17-capable compiler (e.g., `g++`, `clang++`)
- A POSIX-like system is recommended. Windows *might* work with some tweaks, but it hasn’t been tested.

## Project Goals

- Show how OOP design applies to a real(ish) project
- Practice structuring code into classes with clear responsibilities
- Build something a little cooler than “Shape inheritance diagrams”

## License

This project is licensed under the MIT License – see the [LICENSE](./LICENSE) file for details.

## Author

\[Muaviz]
