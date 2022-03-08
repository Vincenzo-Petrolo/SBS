#!/usr/bin/env python3

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

rpm_options = [
    "Trigger ABS => It will try to trigger the ABS of the system",
    "Coherent with speed => Wheels are correctly spinning"
]

brake_pads_wearing_options = [
    "High wearing => Brakes are weared at 90% level",
    "Low wearing => Brakes are weared at 10% level",
    "Custom wearing => You chose the percentage"
]

tyre_pressure_options = [
    "Pressure OK => ",
    "Low Pressure"
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
rpm_value = 0
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

    #choose rpm
    terminal_menu = TerminalMenu(rpm_options)
    menu_entry_index = terminal_menu.show()
    global rpm_value
    if (menu_entry_index == 0):
        rpm_value = 1
        print(Fore.RED +"ABS activation set")
    else:
        rpm_value = 0
        print(Fore.GREEN +"Coherent RPM with speed")

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
    if (menu_entry_index == 0):
        tyre_pressure_value = 1
        print(Fore.GREEN +"High pressure set")
    else:
        tyre_pressure_value = 0
        print(Fore.RED +"Low pressure set")

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

def main():
    print(initial_print)
    scenario_menu()

if __name__ == "__main__":
    main()