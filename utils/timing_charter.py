
import json
import wave

f = open("mountpoint/timings.csv", "r")

time_unit_passed = 1 #at beginning
json_dict = {"signal" : []}

for p in f:
    found = 0
    #remove trailing newline
    p = p.rstrip('\n')
    #cycle through the list of dictionaries
    for x in json_dict["signal"]:
        # search for a matching name
        if (x["name"] == p):
            found = 1
            # if same then it is required to place a .
            if (x["curr_state"] == 'h'):
                x["wave"] += '.'
            else:
                x["wave"] += 'h'
            #update current state of the process
            x["curr_state"] = 'h'
        else:
            # do the same for 0 values
            if (x["curr_state"] == 'l'):
                x["wave"] += '.'
            else:
                x["wave"] += 'l'
            #update current state of the process
            x["curr_state"] = 'l'
    if (found == 0):
        #if the corresponding process was not found, then insert it
        json_dict["signal"].append({"name" : p, "wave" : 'l' + '.'*(time_unit_passed-1) + 'h', "curr_state" : 'h'})
    time_unit_passed += 1

print(json_dict)