import java.util.*;

public class Jthree {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String s1 = "Khetesh Samadhan Deore ";
		String s2 = "      Pramod    Deore          ";
		String s3 = "1234567";
		System.out.println("CharAt(0):" + s1.charAt(0));
		
		System.out.println("Compare:" + s1.compareTo(s2));
		
		System.out.println("Concat :" + s1.concat(" From Computer Science"));
		
		System.out.println("equals :" + s1.equals("Khetesh Samadhan Deore    n")); /// true or flase
		
		String cleaned = s1.trim().replaceAll("\\\\s+", " ");
		// Split into words
		String[] words = cleaned.split(" ");
		System.out.println("Split: s4= " + words);
		
		System.out.println("Trim : " + s2.trim());
	
		System.out.println("tolowercase :" + s1.toLowerCase());
		
		System.out.println("toUpperCase :" + s1.toUpperCase());
		
		System.out.println("length :" + s3.length());

		System.out.println("replace :" + s1.replace('h','H'));
		
	}
}