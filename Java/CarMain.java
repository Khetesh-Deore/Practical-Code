class Car {
	int n;
	String color;

	public Car(int n, String color) {
		this.n = n;
		this.color = color;
	}
	public Car(){
		n=12;
		color="Yellow";
	}

	void StartEngine() {
		System.out.println("Car Engine is Started ");
	}

	void Accelarate() {
		System.out.println("Car is Accelarated");
	}
}

public class CarMain {
	public static void main(String[] args) {
		Car mycar = new Car(10,"Pink");
		Car  Gadi = new Car();
		mycar.StartEngine();
		System.out.println("Color Of gadi :" + Gadi.color);
		System.out.println("Color:" + mycar.color);
		mycar.color = "red";
		System.out.println("Color:" + mycar.color);
		System.out.println("N:" + mycar.n);
		System.out.println("N: for gadi " +Gadi.n);
		System.out.println(mycar);
		System.out.println(Gadi);
	}
}