package assignment9.fitbit;

import jssc.SerialPortException;
import studio4.SerialComm;

public class Fitbit1 {
	final private SerialComm port;
	public static int stepsTaken;
	public static double stepsPerHour;
	public static int currentTemperature;
	public static double amountOfSleep;
	//  "/dev/cu.usbserial-DN01JJ76"
	public Fitbit1(String portName) throws SerialPortException {
		port = new SerialComm(portName);
	}
	
	public static void main(String[] args) throws SerialPortException {
		Fitbit1 newReceive = new Fitbit1("COM3");
		while (true) {
			newReceive.run();
		}
	}
	
	public void run() throws SerialPortException {
		if (port.readByte() == 0x32) {
			byte key = port.readByte();
			switch(key) {
			case 0x50:
				int leftMessage = port.readByte() << 8;
				int rightMessage = port.readByte();
				int totalMessage = leftMessage + rightMessage;
				
				char[] debugMessage = new char[totalMessage];
				for (int i = 0; i <= totalMessage - 1; ++i) {
					byte byteToAdd = port.readByte();
					debugMessage[i] = ((char)byteToAdd);
				}
				System.out.print("Debug Message:");
				System.out.println(debugMessage);
				System.out.println();
				break;
				
			case 0x51: 
				int left = port.readByte() << 8;
				int right = port.readByte();
				int total = left + right;
				
				char[] errorMessage = new char[total];
				for (int i = 0; i <= total - 1; ++i) {
					byte addedByte = port.readByte();
					errorMessage[i] = ((char)addedByte);
				}
				System.out.print("Error Message:");
				System.out.println(errorMessage);
				System.out.println();
				break;
				
			case 0x52:
				long part1 = (port.readByte() & 0xFF) << 24;
				long part2 = (port.readByte() & 0xFF) << 16;
				long part3 = (port.readByte() & 0xFF) << 8;
				long part4 = (port.readByte() & 0xFF);
				long totalParts = part1 + part2 + part3 + part4;
				float tempReading = Float.intBitsToFloat((int)totalParts);
				int tempA = ((int)(tempReading+55));
				System.out.print("Temperature: ");
				System.out.println(tempA);
				System.out.println();
				currentTemperature = tempA;
				break;
				
			case 0x53:
				long run1 = (port.readByte() & 0xFF) << 24;
				long run2 = (port.readByte() & 0xFF) << 16;
				long run3 = (port.readByte() & 0xFF) << 8;
				long run4 = (port.readByte() & 0xFF);
				long totalRun = run1 + run2 + run3 + run4;
				float runTime = Float.intBitsToFloat((int)totalRun);
				System.out.print("Runtime (in Seconds): ");
				System.out.println(runTime / 1000);
				System.out.println();
				break;
				
			case 0x54:
				long sleep1 = (port.readByte() & 0xFF) << 24;
				long sleep2 = (port.readByte() & 0xFF) << 16;
				long sleep3 = (port.readByte() & 0xFF) << 8;
				long sleep4 = (port.readByte() & 0xFF);
				long totalSleep = sleep1 + sleep2 + sleep3 + sleep4;
				float sleepTime = Float.intBitsToFloat((int)totalSleep);
				double timeAsleep = Math.floor(sleepTime*Math.pow(10, 45)/1.4/1.000927474517);
				System.out.print("Time Asleep: ");
				System.out.println(timeAsleep);
				System.out.println();
				amountOfSleep = timeAsleep;
				break;
				
			case 0x55:
				int step1 = (port.readByte() & 0xFF) << 8;
				int step2 = (port.readByte() & 0xFF);
				int totalSteps = step1 + step2;
				System.out.print("Total Steps: ");
				System.out.println(totalSteps);
				System.out.println();
				stepsTaken = totalSteps;
				break; 
				
			case 0x56:
				long ped1 = (port.readByte() & 0xFF) << 24;
				long ped2 = (port.readByte() & 0xFF) << 16;
				long ped3 = (port.readByte() & 0xFF) << 8;
				long ped4 = (port.readByte() & 0xFF);
				long totalPedTime = ped1 + ped2 + ped3 + ped4;
				stepsPerHour = stepsTaken/totalPedTime;
				System.out.print("Steps Per Hour: ");
				System.out.println(stepsPerHour);
				System.out.println();
				break;
				
			default:
				System.out.println("~~~ Start ~~~");
				System.out.println();
				break;
			}
		}
	}
}