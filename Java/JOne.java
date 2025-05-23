import java.util.*;

class Acc {
	int Accno;
	String Name;
	int bal;
	int interest;
	String email;
	String Add;
	int rate = 12;

	void InputTake(Scanner sc) {
		System.out.println("Enter the Name :");
		this.Name = sc.nextLine();
		System.out.print("Enter the Account Number :");
		this.Accno = sc.nextInt();
		System.out.print("Enter initail Balance :");
		this.bal = sc.nextInt();
		sc.nextLine();
		System.out.print("Enter the Email :");
		this.email = sc.nextLine();
		System.out.print("Enter the Address :");
		this.Add = sc.nextLine();
	}

	void Display() {
		System.out.println("Name:" + this.Name);
		System.out.println("Account No. : " + this.Accno);
		System.out.println("Balance :" + this.bal);
		System.out.println("Email: " + this.email);
		System.out.println("Address :" + this.Add);

	}

	void Disbal() {
		System.out.println("Balance :" + this.bal);
	}

	void AddDeposite(Scanner sc) {
		float deposite;
		System.out.println("Enter the Amount is to  Deposited :");
		deposite = sc.nextFloat();
		this.bal += deposite;
		System.out.println("Balance :" + this.bal + "Amount deposited:" + deposite);
	}

	void withdraw(Scanner sc) {
		float with;
		System.out.println("Enter the amount for Withdraw :");
		with = sc.nextFloat();
		if (this.bal < with) {
			System.out.println("Not enough Balance ");
		} else {
			this.bal -= with;
		}
		System.out.println("Balance :" + this.bal);
	}

	void computeInterest(Scanner sc) {
		float years;
		System.out.println("No of Years:");
		years = sc.nextFloat();
		System.out.println("INterest iss " + this.bal * years * this.rate / 100);
	}
}

public class JOne {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Acc user = new Acc();
		int choice;
		do {
			System.out.println(
					"Enter Choice\n1.Input\n2.Display\n3.Display Balance\n4.Add Deposite\n5.Withdraw\n6.Compute Interest\n7.Exit");
			choice = sc.nextInt();
			sc.nextLine();
			switch (choice) {
				case 1:
					user.InputTake(sc);
					break;
				case 2:
					user.Display();
					break;
				case 3:
					user.Disbal();
					break;
				case 4:
					user.AddDeposite(sc);
					break;
				case 5:
					user.withdraw(sc);
					break;
				case 6:
					user.computeInterest(sc);
					break;
				case 7:
					System.out.println("Exiting...............");
					break;
				default:
					System.out.println("Invalid choice ");
			}

		} while (choice != 7);
	}
}