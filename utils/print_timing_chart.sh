#!/bin/bash

mkdir -p mountpoint
sudo mount sd.bin mountpoint
python utils/timing_charter.py
sudo umount mountpoint