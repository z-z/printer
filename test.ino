#include <SoftwareSerial.h>
#include <Vector.h>

char *commands[] = {
//	"G0 X0 Y0 F2000",
//	"G0 X100 Y0 F2000",
//	"G0 X100 Y100 F2000",
//	"G0 X0 Y100 F2000"

//	"X0 Y0 F3600",
//	"X0 Y300 F3600",
//	"X30 Y-210 F3600",
//	"X150 Y90 F3600",
//	"X270 Y-210 F3600",
//	"X0 Y0 F3600",

	"X0 Y0 F3600",
	"X-50 Y180 F3600",
	"X0 Y0 F3600",

//	"G0 X8.71808000 F940.80000000",
//	"G0 X17.42048000 F940.80000000",
//	"G0 X26.13856000 F940.80000000",
//	"G0 X31.32854200 F746.76000000",
//	"G0 X33.90169000 F1118.76000000",
//	"G0 X42.61977000 F940.80000000",
//	"G0 X47.80975200 F746.76000000",
//	"G0 X50.40154600 F1118.76000000",
//	"G0 X67.82202600 F940.80000000",
//	"G0 X80.86119600 F1409.64000000",
//	"G0 X93.92386000 F1409.64000000",
//	"G0 X106.96303000 F1409.64000000",
//	"G0 X117.34216000 F1493.40000000",
//	"G0 X119.93395400 F1118.76000000",
//	"G0 X128.14795400 F888.00000000",
//	"G0 X133.33793600 F746.76000000",
//	"G0 X135.92973000 F1118.76000000",
//	"G0 X153.35021000 F940.80000000",
//	"G0 X170.78637000 F1881.60000000",
//	"G0 X177.30925000 F940.80000000",
//	"G0 X179.48877000 F940.80000000",
//	"G0 X162.05261000 F1881.60000000"
};

int cmdNum = 0;

SoftwareSerial motorsSerial(10, 11); // RX, TX

void setup()
{
	Serial.begin(9600);
	while(!Serial){;}
	motorsSerial.begin(9600);
}

void loop()
{
	while(Serial.available() > 0)
	{
		Serial.readString();

		if(cmdNum == 4)
			cmdNum = 0;

		String cmd = String(commands[cmdNum]);

		Serial.println("send command " + cmd);

		for(int i = 0; i < cmd.length(); i++)
			motorsSerial.write(byte(cmd.charAt(i)));

//		motorsSerial.write(byte("\n"));

		cmdNum++;
	}
}


// UNO
