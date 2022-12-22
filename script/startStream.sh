#!/bin/bash

while true; do
  # Set the URL of the YouTube video
  url="https://www.youtube.com/watch?v=LLHt5P36B8E"

  # Set the output file name
  output_file="trafficStream.mp4"

  # Set the start time to be the current time minus 5 seconds
#   start_time=$(date +%s --date='5 seconds ago')

#   end_time= $date

  start_time=$date

  # Use ydl to download the latest 5 seconds of the video and convert it to MP4 format
  youtube-dl --format "mp4" --output "$output_file" --postprocessor-args "-t 0:0:5" "$url"

  mv "$output_file" ../bin/

  clear
  # Prompt the user to press Enter to continue
  read -p "Press Enter to stop, any other key to continue..."

  # If the user pressed Enter, break the loop
  if [[ $REPLY == "" ]]; then
    break
  fi
done
