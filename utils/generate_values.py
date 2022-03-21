#!/usr/bin/env python3

from email import header
import colorama
from colorama import Fore
from simple_term_menu import TerminalMenu

proximity_options = [
            "Far from obstacle => Simulation starts when bus is far from obstacle",
            "Close to obstacle => Simulation srtars when bus is close to obstacle",
            "Custom proximity => You choose the value in meters"
]

humidity_options = ["Wet Road => High humidity close to 90%",
             "Dry Road => Low humidity close to 20%", 
             "Custom Humidity => You choose the percentage"]

speed_options = [
    "High speed : Starting simulation at 80 km/h",
    "Low speed : Starting simulation at 30 km/h",
    "Custom speed : You choose the value"
]

brake_pads_wearing_options = [
    "High wearing => Brakes are weared at 90% level",
    "Low wearing => Brakes are weared at 10% level",
    "Custom wearing => You chose the percentage"
]

tyre_pressure_options = [
    "Pressure OK => 90% of the ideal value ",
    "Low Pressure => 20% of the ideal value",
    "Custom value => You choose the value in meters"
]

people_onboard_options = [
    "Crowdy => 80 people on the bus",
    "Almost empty => 10 people on the bus",
    "Custom crowd => Insert the number of people (Max is 80, Min is obviously 0)"
]

initial_print = "Welcome to the values generator, please choose options from the menu entries to generate a .h header file that contains the values to be fed to"\
                "sensors present on the bus."

proximity_value = 0
humidity_value = 0
speed_value = 0
brake_pads_wearing_value = 0
tyre_pressure_value = 0
people_onboard_value = 0



def scenario_menu():
    # Choose proximity
    terminal_menu = TerminalMenu(proximity_options)
    menu_entry_index = terminal_menu.show()
    global proximity_value
    if (menu_entry_index == 2):
        proximity_value = int(input("Insert the custom value: "))
    elif (menu_entry_index == 0):
        proximity_value = 300
    else:
        proximity_value = 50
    print(Fore.GREEN + "Proximity set to:" + str(proximity_value))

    #choose humidity

    terminal_menu = TerminalMenu(humidity_options)
    menu_entry_index = terminal_menu.show()
    global humidity_value
    if (menu_entry_index == 2):
        humidity_value = int(input("Insert the custom value: "))
    elif (menu_entry_index == 0):
        humidity_value = 90
    else:
        humidity_value = 20
    print(Fore.GREEN +"Humidity set to:" + str(humidity_value))

    #choose speed
    terminal_menu = TerminalMenu(speed_options)
    menu_entry_index = terminal_menu.show()
    global speed_value
    if (menu_entry_index == 2):
        speed_value = int(input("Insert the custom value: "))
    elif (menu_entry_index == 0):
        speed_value = 80
    else:
        speed_value = 30
    print(Fore.GREEN +"Speed set to:" + str(speed_value))

    #choose brake pads wearing
    terminal_menu = TerminalMenu(brake_pads_wearing_options)
    menu_entry_index = terminal_menu.show()
    global brake_pads_wearing_value
    if (menu_entry_index == 2):
        brake_pads_wearing_value = int(input("Insert the custom value: "))
    elif (menu_entry_index == 0):
        brake_pads_wearing_value = 90
    else:
        brake_pads_wearing_value = 10
    print(Fore.GREEN +"Brake pads wearing set to:" + str(brake_pads_wearing_value))

    # choose tyre pressure
    terminal_menu = TerminalMenu(tyre_pressure_options)
    menu_entry_index = terminal_menu.show()
    global tyre_pressure_value
    if (menu_entry_index == 2):
        tyre_pressure_value = int(input("Insert the custom value: "))
    elif (menu_entry_index == 0):
        tyre_pressure_value = 90
    else:
        tyre_pressure_value = 20
    print(Fore.GREEN +"Tyre pressure set to:" + str(tyre_pressure_value))

    # choose no. people onboard
    terminal_menu = TerminalMenu(people_onboard_options)
    menu_entry_index = terminal_menu.show()
    global people_onboard_value
    if (menu_entry_index == 2):
        people_onboard_value = int(input("Insert the custom value: "))
    elif (menu_entry_index == 0):
        people_onboard_value = 80
    else:
        people_onboard_value = 10
    print(Fore.GREEN +"People present on bus set to:" + str(people_onboard_value))

def generate_headerfile():
    headerfile = open("sensors_header.h", "w")
    headerfile.write("#ifndef __SENSORS_CONFIG_H__\n")
    headerfile.write("#define __SENSORS_CONFIG_H__\n")

    #write proximity starting value
    headerfile.write("unsigned int proximity_start = " + str(proximity_value) + ";\n")
    headerfile.write("unsigned int humidity_value = " + str(humidity_value) + ";\n")
    headerfile.write("unsigned int initial_speed = " + str(speed_value) + ";\n")
    headerfile.write("unsigned int brake_pads_wearing_value = " + str(brake_pads_wearing_value) + ";\n")
    headerfile.write("unsigned int tyre_pressure_value = " + str(tyre_pressure_value) + ";\n")
    headerfile.write("unsigned int people_onboard = " + str(people_onboard_value) + ";\n")

    headerfile.write("#endif")
    headerfile.close()
    pass

def main():
    print(Fore.YELLOW + initial_print)
    scenario_menu()
    generate_headerfile()

if __name__ == "__main__":
    main()