# EX3
FlightGear, Stone 1 Course 89210

This project purpose is to connect to the flight gear simulator as a server that reads the aircraft 
data (fit, speed...) and connect to it as client that updating the data in the simulator.
How we do it? 
We are given a text file fly.txt that has commands, our project read them from it and executing them one by one.
In the project we are running 3 threads: the main thread that executing the commands, the server thread and the client tread.
The goal of the project is to make the aircraft to take off safetly and get to 1,000 fit when it done we close all the 
connections and finishing.

to run that project we need to install few things:
First of all the flightgear simulator you can install it from here ‫‪/‫‪http://home.flightgear.org‬‬
In the git you can find the generic_small.xml go to the  directory of the simulator and insert it to 
the protocol directory. 
when you run the simulator, go to Settings-> Additional Settings and put there those line 
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
--telnet=socket,in,10,127.0.0.1,5402,tcp
if you dont have telnet for windows search ‫‪"install‬‬ ‫‪telnet‬‬ ‫‪client‬‬ ‫‪windows‬‬ ‫‪10‬‬ ‫‪command‬‬ ‫‪line‬‬", in linux you can
download it from the terminal.
now run the project, when it's running open the simulator and run it too. all that you got to do is sit tight 
and enjoy the nice take off of the aircraft.

For support you can email us:
shai.acoca@gmail.com
omer2445@gmail.com 

Project status, stone 1 is finished and ready waiting for more instructions on the continue stones.
