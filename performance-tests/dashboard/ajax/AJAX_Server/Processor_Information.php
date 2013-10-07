<?php
set_time_limit(0);

$processor_info_file_name = '/usr/SEM/trunk/SEM/OASIS/performance-tests/dashboard/ajax/Processor_Info.txt';
$processor_info_file_last_modified_time = 0;

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
    $processor_info_file_modified_time = filemtime($processor_info_file_name );
    $processor_info = "";

    if ($processor_info_file_last_modified_time < $processor_info_file_modified_time)  
    {
        $processor_info_file_last_modified_time = $processor_info_file_modified_time;
        $handle = fopen($processor_info_file_name,"r");
        $processor_info = fgets ($handle);
        fclose ($handle);
        echo $processor_info."<br/>";
    }
    flush2();
    clearstatcache();
}

?>
