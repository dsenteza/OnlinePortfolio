package assignment10.fitbit;

import assignment9.fitbit.Fitbit1;
import jssc.SerialPortException;
import studio4.SerialComm;
import java.awt.Color;
import java.awt.Font;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import sedgewick.StdDraw;

public class Fitbit2 {
	final private SerialComm port;
	public static int stepsTaken;
	public static double stepsPerHour;
	public static int currentTemperature;
	public static double amountOfSleep;
	public static double time = 1030;
	
	public Fitbit2(String portName) throws SerialPortException {
		port = new SerialComm(portName);
	}
	
	public static void main(String[] args) throws SerialPortException {
		Fitbit2 newReceive = new Fitbit2("COM3");
		while (true) {
			newReceive.run();
		}
	}
	
	public void run() throws SerialPortException {
		if (port.readByte() == 0x32) {
			byte key = port.readByte();
			switch(key) {	
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
				stepsPerHour = stepsTaken/totalPedTime*(3600);
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
	
//	public void graph() {
//		while (inputStream.hasNext()) {
//			String data = inputStream.next();
//			String strar[] = data.split(",");
//			double d = Double.parseDouble(strar[1]);
//			System.out.println(d);
//			draw(d);
//			time += 30;
//		}
//	}
	
	public static void draw(double y) {
		StdDraw.setPenColor(Color.RED);
		StdDraw.setPenRadius(0.01);
		StdDraw.point(time, y);
	}
}
