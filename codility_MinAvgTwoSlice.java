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
        double cut_head_avg;
        double all_avg;
        double new_avg;
        for (int i = 2 ; i < A.length ; i ++) {
            all_avg = (cands[cur_cand].total+A[i])/(1.0*cands[cur_cand].count+1);
            cut_head_avg = (1.0*cands[cur_cand].total+A[i]-A[cands[cur_cand].start])/(1.0*cands[cur_cand].count);
            new_avg = (A[i-1]+A[i])/2.0;
            //System.out.println("all_avg;"+all_avg);
            //System.out.println("cut_head_avg;"+cut_head_avg);
            //System.out.println("new_avg;"+new_avg);
            if (cands[cur_cand].avg < A[i]|| new_avg < all_avg && new_avg < cut_head_avg) {
                cur_cand++;
                cands[cur_cand] = new cand(i-1,A[i-1],A[i]);
                continue;
            }
            if(all_avg > cut_head_avg) {
               cands[cur_cand].total = cands[cur_cand].total+A[i]-A[cands[cur_cand].start];
               cands[cur_cand].avg = cut_head_avg;
               cands[cur_cand].start ++;
               cands[cur_cand].end = i;
            } else {
                cands[cur_cand].total += A[i];
               cands[cur_cand].avg = all_avg;
               cands[cur_cand].count ++;
               cands[cur_cand].end = i;
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
