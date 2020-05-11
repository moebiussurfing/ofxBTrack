# ofxBTrack
openFrameworks Addon for Real-Time Beat Tracking - Based on Adam Stark's BTrack algorithm

## NOTE
**[FORK] This is a modified version of ofxBTrack / BTrack sources to allow Windows/VS2017 compatible.**  

- modified example-audioInput.  
- added some dependencies. check code.  


## Screenshot
![Alt text](/screenshot.PNG?raw=true "screenshot")

-------------------------------------------------------------------------------------------

BTrack  
https://github.com/adamstark/BTrack 

btrack~: Max/MSP external  
https://github.com/naotokui/btrack_external 

### notice  
This is an addon for beat tracking, not for onset detection! Each occurance of sudden attack/inpulse of sound (onset) doesn't matter in this case. Instead, the algorighm tries to find a constant beat and track the location of each beat in incoming audio signal. 

