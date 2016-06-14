// you can also use imports, for example:
// import java.util.*;

// you can write to stdout for debugging purposes, e.g.
// System.out.println("this is a debug message");

class Solution {
    class cand {
        public int start;
        public int end;
        public int total;
        public int count;
        public double avg;
        public cand(int start, int a, int b) {
            this.start = start;
            this.total = a+b;
            this.end = start+1;
            this.count = 2;
            this.avg = total/(count*1.0);
            //System.out.println("start;"+start);
            //System.out.println("avg;"+avg);
        }
    }
    public int solution(int[] A) {
        // write your code in Java SE 8
        cand cands[] = new cand[A.length];
        
        int cur_cand = 0;
        cands[cur_cand] = new cand(0,A[0],A[1]);
        for (int i = 2 ; i < A.length ; i ++) {
            if(cands[cur_cand].avg > A[i] && cands[cur_cand].avg < A[i-1]+A[i]/2.0) {
                double exp_avg = (cands[cur_cand].total + A[i])/((cands[cur_cand].count+1)* 1.0);
                double cut_head_avg = (cands[cur_cand].total + A[i] - A[cands[cur_cand].start])/(cands[cur_cand].count)* 1.0;
                //System.out.println("i,cur_cand;"+i+","+cur_cand);
                //System.out.println("exp_avg,cut_head_avg;"+exp_avg+","+cut_head_avg);
                if(exp_avg > cut_head_avg && cands[cur_cand].count >  1 ){
                    cands[cur_cand].total -= A[cands[cur_cand].start];                   
                    cands[cur_cand].start++;
                    cands[cur_cand].count--;
                }
                cands[cur_cand].end = i;
                cands[cur_cand].total+=A[i];
                cands[cur_cand].count++;
                cands[cur_cand].avg = cands[cur_cand].total / (cands[cur_cand].count * 1.0);
                /*
                System.out.println("i,cur_cand;"+i+","+cur_cand);
            System.out.println("cand.avg;"+cands[cur_cand].avg);
            System.out.println("cand.start;"+cands[cur_cand].start);
            System.out.println("cand.end;"+cands[cur_cand].end);
            System.out.println("cand.count;"+cands[cur_cand].count);
            System.out.println("cand.total;"+cands[cur_cand].total);
            System.out.println("-----");
            */
            } else {
                cur_cand++;
                try{
                cands[cur_cand] = new cand(i-1,A[i-1],A[i]);
                //i++;
                }catch (Exception e) {
                    //System.out.println("Exception.cur_cand;"+cur_cand);
                    cur_cand--;
                }
            }            
        }
        int answer = cur_cand;
        for (int i = cur_cand ; i >= 0 ; i --) {
            /*
            System.out.println("i;"+i);
            System.out.println("cand.avg;"+cands[i].avg);
            System.out.println("cand.start;"+cands[i].start);
            System.out.println("cand.end;"+cands[i].end);
            System.out.println("cand.count;"+cands[i].count);
            System.out.println("cand.total;"+cands[i].total);
            System.out.println("-----");
            */
           if( cands[answer].avg >= cands[i].avg ) {
               answer = i ;
           }
        }
        /*
        System.out.println("answer;"+answer);
        System.out.println("cand.avg;"+cands[answer].avg);
        System.out.println("cand.start;"+cands[answer].start);
        System.out.println("cand.end;"+cands[answer].end);
        System.out.println("cand.count;"+cands[answer].count);
        System.out.println("cand.total;"+cands[answer].total);
        */
        return cands[answer].start;
    }
}
