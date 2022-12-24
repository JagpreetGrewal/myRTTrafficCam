#!/bin/bash

while true; do
  # Set the URL of the YouTube video
  url="https://www.youtube.com/watch?v=LLHt5P36B8E"

  # Set the output file name, have it output to the script directory
  output_file="trafficStream.mp4"

  start_time="0:00:5"

  end_time="0:00:10"

  ./processStream.sh "$url" "$start_time" "$end_time" "$output_file"

  ../bin/processVideo
  # Prompt the user to press Enter to continue
  read -ep "Press Enter to stop, any other key to continue: "

  # If the user pressed Enter, break the loop
  if [[ $REPLY == "" ]]; then
    echo "Shutting down..."
    break
  fi
done
