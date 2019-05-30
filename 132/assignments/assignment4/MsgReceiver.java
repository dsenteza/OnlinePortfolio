package assignment4;

import java.io.IOException;
import jssc.SerialPort;
import jssc.SerialPortException;
import studio4.SerialComm;

public class MsgReceiver {

	final private SerialComm port;

	public MsgReceiver(String portname) {
		port = new SerialComm(portname);
	}

	public enum labEnum {
		magic, key, message,
		timeStamp, potentiometer, rawCount,
		temp, filtered
	}

	labEnum cases = labEnum.key;
	byte key1;

	public void run() throws SerialPortException{
		while (true) {
			if (port.readByte() == 0x21) {
				key1 = port.readByte();
				cases = labEnum.key;
			}

			switch (cases) {

			//                                                             case magic:
				//                                                                             break;

			case key:
				if (key1 == 0x30 || key1 == 0x31) {
					cases = labEnum.message;
				}
				if (port.readByte() == 0x32) {
					cases = labEnum.timeStamp;
				}
				if (port.readByte() == 0x33) {
					cases = labEnum.potentiometer;
				}
				if (port.readByte() == 0x34) {
					cases = labEnum.rawCount;
				}
				if (port.readByte() == 0x35) {
					cases = labEnum.temp;
				}
				if (port.readByte() == 0x36) {
					cases = labEnum.filtered;
				}
				break;

			case message:
				byte firstHalf = port.readByte();
				byte secondHalf = port.readByte();
				int val1 = firstHalf << 8;
				int val2 = secondHalf;
				int combinedMes = val1 + val2;
				//                                                                             System.out.println("Message: ");
				//                                                                             System.out.println(combinedMes);
				for (int i = 0; i < combinedMes; i++) {
					System.out.println((char)port.readByte());
				}
				break;

			case timeStamp:
				System.out.println("Timestamp: ");
				int first = convert(port.readByte()) << 24;
				int second = convert(port.readByte()) << 16;
				int third = convert(port.readByte()) << 8;
				int fourth = convert(port.readByte());
				System.out.println(first + second + third + fourth);
				break;

			case potentiometer:
				System.out.println("Potentiometer: ");
				int firstVal = convert(port.readByte()) << 8;
				int secVal = convert(port.readByte());
				System.out.println(firstVal + secVal);
				break;

			case rawCount:
				System.out.println("Raw Count: ");
				int firstRaw = convert(port.readByte()) << 24;
				int secondRaw = convert(port.readByte()) << 16;
				int thirdRaw = convert(port.readByte()) << 8;
				int fourthRaw = convert(port.readByte());
				System.out.println(firstRaw + secondRaw + thirdRaw
						+ fourthRaw);
				break;

			case temp:
				System.out.println("Temperature: ");
				int firstTemp = convert(port.readByte()) << 24;
				int secondTemp = convert(port.readByte()) << 16;
				int thirdTemp = convert(port.readByte()) << 8;
				int fourthTemp = convert(port.readByte());
				System.out.println(firstTemp + secondTemp +
						thirdTemp + fourthTemp);
				break;

			case filtered:
				System.out.println("Filtered: ");
				int firstAvg = convert(port.readByte()) << 24;
				int secondAvg = convert(port.readByte()) << 16;
				int thirdAvg = convert(port.readByte()) << 8;
				int fourthAvg = convert(port.readByte());
				System.out.println(firstAvg + secondAvg +
						thirdAvg + fourthAvg);
				break;
			default:
				break;
			}
		}
	}

	int convert(byte reading) {
		if (reading <= 255 && reading >= 0) {
			int number = reading;
			return number;
		}
		int number = (reading & 255) + 256;
		return number;
	}

	public static void main(String[] args) throws SerialPortException {
		MsgReceiver msgr = new MsgReceiver("/dev/cu.usbserial-DN01JJ76"); // Adjust this to be the right port for your machine
		msgr.run();
	}
}