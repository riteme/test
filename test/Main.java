import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        try {
            BufferedReader bi = new BufferedReader(new InputStreamReader(System.in));
            HashSet hs = new HashSet();
            int n = Integer.parseInt(bi.readLine());
            String line = bi.readLine();
            for (String numStr: line.split("\\s")) {
                int v = Integer.parseInt(numStr);
                hs.add(v);
            }
            boolean ok = true;
            for (int i = 1; i <= n && ok; i++) {
                if (!hs.contains(i)) ok = false;
            }
            if (ok) System.out.println("Yes");
            else System.out.println("No");
        } catch(Exception e) {
        }
    }
}
