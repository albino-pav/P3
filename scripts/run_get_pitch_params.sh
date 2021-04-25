#!/bin/bash

# Put here the program (maybe with path)
GETF0="get_pitch"

for pot in $(seq 35 1 45); do
  for rmax in $(seq 0.2 0.1 0.4); do
    for r1 in $(seq 0.6 0.1 0.9); do
      for fwav in pitch_db/train/*.wav; do
        ff0=${fwav/.wav/.f0}
        $GETF0 $fwav $ff0 $r1 $rmax $pot > /dev/null || (echo "Error in $GETF0 $fwav $ff0"; exit 1)
      done
      echo "r1: $r1 rmax: $rmax pot: $pot" >> res.txt
      pitch_evaluate pitch_db/train/*.f0ref | fgrep TOTAL >> res.txt
    done
  done
done

exit 0
