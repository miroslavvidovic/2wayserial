<#
    Read data from arduino on COM3 and send feddback information
    on the same port
#>
    # Define the COM port
    $port= new-Object System.IO.Ports.SerialPort COM3,9600,None,8,one

    # Open the serial port and read the data
    $port.open(); 
    while ($port.IsOpen) {
        $data = [int] $port.ReadLine()
        write-host $data

        if($data -eq 2) {
            Write-Host ("two");
            $port.WriteLine("TWO");
        }
    }