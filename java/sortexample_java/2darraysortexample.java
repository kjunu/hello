import java.util.Arrays;
import java.util.Comparator;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.net.URI;
 
 
public class Main {
    public static void main(String[] args) throws Exception {
        URI uri = new URI(Main.class.getResource("").getPath() + "sample_input.txt");
        System.setIn(new FileInputStream(uri.getPath()));
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        String t = "";
        t = sc.readLine();
        int count = Integer.parseInt(t);
        int[][] coloredPapers = new int[count+1][2];
        coloredPapers[0][0] = 0;
        coloredPapers[0][1] = 0;
        for(int i =1; i< count+1 ; i++){
            t = sc.readLine();
            String[] tt = t.split(" ");
            int x = Integer.parseInt(tt[0]);
            int y = Integer.parseInt(tt[1]);
            coloredPapers[i][0] = (Math.min(x, y));
            coloredPapers[i][1] = (Math.max(x, y));
        }
 
        Arrays.sort(coloredPapers, new Comparator<int[]>(){
            @Override
            public int compare(int[] o1, int[] o2) {
                if(o1[0] > o2[0]){
                    return 1;
                }
                else{
                    if(o1[0] < o2[0]){
                        return -1;
                    }
                    else{
                        return Integer.compare(o1[1], o2[1]);
                    }
                }
            }
        });
        int[] temp = new int[count+1];
        int result = 0;
        for(int i = 1; i < count+1; i++){
            int temp_max = 0;
            for(int j = 0; j < i; j++){
                if(coloredPapers[i][1]>= coloredPapers[j][1]){
                    if(temp_max < temp[j]){
                        temp_max = temp[j];
                    }
                }
            }
            temp[i] = temp_max+1;
            if(temp[i]>result) result = temp[i];
        }
        System.out.println(result);
    }
}
