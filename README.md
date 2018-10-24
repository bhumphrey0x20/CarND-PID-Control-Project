# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

### Implementation

The equation in Figure 1 is the continuous time PID controller equation. The PID controller for this project takes the crosstrack error (CTE) provided by the simulator and calculates a proportional error, an integral error, and a derivative error. The proportional error is simply the CTE, the integral error is the sum of all the previous CTEs received upto the current point. The derivative error is the current CTE minus the previous CTE. Proportional (Kp), integral (Ki), and derivative (Kd) gains are multiplied by their respective errors and summed. In this project manual tuning of the gains was performed. 

#### Figure 1: PID Equation
<img src="https://github.com/bhumphrey0x20/CarND-PID-Control-Project/blob/master/PIDController_Equation.png" height="120" width="240" />
[* Image from http://wiki.theuavguide.com/wiki/File:PIDController_Equation.png ]

The CTE is passed as an argument to `pid.UpdateError()` in main.cpp ( line 82). PID.cpp contains the function definition for `pid.UpdateError()`, here the proportional, integral and derivative errors are calculated (lines 27-40) and saved as variables in the class PID. Next, in main.cpp the function `pid.pid_cntl()` (line 83) is called to calculate the PID equation (line 47-51). `pid.pid_cntl()` returns the updated steering angle based on the PID equation. Note the equation in the code is a negative sum to compensate for the simulator steering calculations (were turning left, counter-clockwise, is negative and right clockwise is positive). 

#### Table 1. Gain Values for Project
| PID Gain   | Values   | 
| ---------- |:-------------:|
|  Kp        | 0.03     |
|  Ki        | 0.01     |
|  Kd        | 0.7     |

### Reflection
In the implementation, the table below was used as a guide for tuning of each gain component in the algorithm. Increasing the proportional gain (Kp) increased overshoot, this was used at the start for handing sharping turns, this also increased occilations in straightline driving (increased settling time). Increasing the integral gain (Ki) was also used for making turns, but also increases occilations afterward (increasing settling time). Increasing the derivaive gain (Kd) was used to counteract the affects of the overshoot created by Kp and Ki (i.e. not turning to far on turns) while helping to minimize additional occilations (settling time). However, increasing Kd too much created instability in driving, resulting in the car turning circles off the track. 


#### Table 2. Affect of increasing gains on step responce*
| PID Gain   | % Overshoot   | Settling Time | Steady-State Error  |
| ---------- |:-------------:| -------------:| -------------------:|
|  Kp        | Increases     | Minimal Impact| Decreases           |
|  Ki        | Increases     | Increases     | Zero Impact on SS Err|
|  Kd        | Decreases     | Decreases     | No Impact           |
###### * Taken from Dorf, Richard C. and Robert H Bishop, `Modern Control Systems, 12th Ed.` pg 483. Prentice Hall, NJ, 2011.

Tuning of the gains was performed using Table 1 as a guide, additionally the Kp was found using the manual tuning recommendation from Dorf, Richard C. and Robert H Bishop, `Modern Control Systems, 12th Ed.` pg. 483. Prentice Hall, NJ, 2011. Ki and Kd were set at 0 while Kp was increased from 0 until the car was immediately unstable. Then this value of Kp was devided by 2. Next Kd was increase until the car drove reasonable well at straightline driving. Then Ki and Kd (and occasionally Kp) were adjusted to make take turns and stabilze driving. 

#### Video of PID Controlled Car


<a href="https://youtu.be/j1J_kFE4kjM" target="_blank"><img src="https://i.ytimg.com/vi/j1J_kFE4kjM/2.jpg" alt="PID Controller Video" width="240" height="180" border="10" /></a>

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

