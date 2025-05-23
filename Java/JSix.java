import java.io.*;
import java.util.Scanner;

public class JSix {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the file name (with path if not in same folder): ");
        String fileName = sc.nextLine();

        File file = new File(fileName);

        if (!file.exists()) {
            System.out.println("File does not exist.");
            return;
        }

        BufferedReader reader = new BufferedReader(new FileReader(file));
        String line;
        int lineCount = 0, wordCount = 0, charCount = 0;

        while ((line = reader.readLine()) != null) {
            lineCount++;

            // Count characters (including spaces)
            charCount += line.length();

            // Split line into words based on whitespace
            String[] words = line.trim().split("\\s+");
            if (!line.trim().isEmpty()) {
                wordCount += words.length;
            }
        }

        reader.close();

        System.out.println("Lines: " + lineCount);
        System.out.println("Words: " + wordCount);
        System.out.println("Characters: " + charCount);
    }
}
