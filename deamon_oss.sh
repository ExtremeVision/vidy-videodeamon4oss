#!/sh/bin

#Description: 

#This is a deamon and excute process to make sure that all videos in an hour are safely processed. 
#Two main goals for this scripts are as follow: 
#1. The number of video record for an hour may be more than one, they are sorted by order like 0.flv,1.flv... 
#2. Sometimes, processing an single video file will be disrupted by some reasons, so, the second goal for this script is to make sure after disrupted, analysis will be continued and begin from the frame that disrupted at last time.

#$1:camera id.
#$2:absolute path of analysis process.
#$3:oss address.

#sample: sh deamon_oss.sh 161 video_test http://extremevision-cjcs.oss-cn-hangzhou.aliyuncs.com/test_folder/cjcs


#get current date and time.
day=$(date +%d)
month=$(date +%m)
year=$(date +%Y)
an_hour=$(date -d "1 hour ago" +%H)

#init
filepath="/usr/local/vidy-videodeamon4oss"
filename=${filepath}"/files/framepos_"$1"_"${an_hour}"h.txt"
echo '0' > $filename
#set $pos=0
command="cat "${filename}
pos=$($command) 

#init log file
logfile=${filepath}"/files/log_"$1"_"${year}"-"${month}"-"${day}"-"${an_hour}".log"
echo $logfile > $logfile

#oss address.
oss_addr=$3

#loop videos in an hour.
#if no video, $pos=-1
video_num=-1
total_frame_num=0
while true
do
	echo '0' > $filename
	#set $pos=0
	command="cat "${filename}
	pos=$($command)

	video_num=$(($video_num + 1))
	video=${oss_addr}"/"$1"/"${year}"/"${month}"/"${day}"/"${an_hour}"/"${video_num}".flv"
	command=${filepath}"/GetTotalFrameNum "$video
        total_frame_num=$($command)
	if [ $total_frame_num -le 0 ]
	then
		break
	fi
	echo $video >> $logfile
	while [ $pos -lt $total_frame_num ]
	do
        	#[analysis process] [video address] [video date] [video hour] [frame position file] 
		proc=$2" "$1" "$video" "$(date +"%Y%m%d")" "$an_hour" "$filename
#                #excute
                $proc
                echo $proc >> $logfile
		command="cat "${filename}
        	pos=$($command)
		echo "POS:--------------"${pos} >> $logfile
	done
done

echo "process finished!" >> $logfile
