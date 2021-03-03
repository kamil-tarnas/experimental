#!/bin/bash
dpkg -l | grep gcc | awk '{print $2}'
