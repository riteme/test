import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String string = input.nextLine();
        String[] strings = string.split(" ");
        for (String s : strings) {
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.append(Character.toUpperCase(s.charAt(0)));
            for (int i = 1; i < s.length(); i++)
                stringBuilder.append(Character.toLowerCase(s.charAt(i)));
            System.out.print(stringBuilder.toString() + " ");
        }
    }
}
