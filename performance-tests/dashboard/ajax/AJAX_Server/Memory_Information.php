<?php
set_time_limit(0);

$memory_info_file_name = '/usr/SEM/trunk/SEM/OASIS/performance-tests/dashboard/ajax/Memory_Info.txt';
$memory_info_file_last_modified_time = 0;

header("Expires: Sun, 20 Jan 1985 00:00:00 GMT"); // date in the past
header("Cache-Control: no-cache");
header("Pragma: no-cache");
header("Access-Control-Allow-Origin: *");

function flush2 (){
    echo(str_repeat(' ',256));
    // check that buffer is actually set before flushing
    if (ob_get_length()){            
        @ob_flush();
        @flush();
        @ob_end_flush();
    }    
    @ob_start();
}

while(true) 
{
	$memory_info_file_modified_time = filemtime($memory_info_file_name);
	$memory_info = "";
	if ($memory_info_file_last_modified_time < $memory_info_file_modified_time)
	{
		$memory_info_file_last_modified_time = $memory_info_file_modified_time;
        $handle = fopen($memory_info_file_name,"r");
        $memory_info = fgets ($handle);
        fclose ($handle);
        echo $memory_info."<br/>";
	}
    flush2();
    clearstatcache();
}

?>
