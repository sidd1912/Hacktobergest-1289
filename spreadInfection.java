import java.io.*;
import java.util.*;

public class Main {
   static class Edge {
      int src;
      int nbr;

      Edge(int src, int nbr) {
         this.src = src;
         this.nbr = nbr;
      }
   }
   static class pair{
       int src;
       int time;
       pair(int src, int time){
           this.src=src;
           this.time=time;
       }
   }

   public static void main(String[] args) throws Exception {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

      int vtces = Integer.parseInt(br.readLine());
      ArrayList<Edge>[] graph = new ArrayList[vtces];
      for (int i = 0; i < vtces; i++) {
         graph[i] = new ArrayList<>();
      }

      int edges = Integer.parseInt(br.readLine());
      for (int i = 0; i < edges; i++) {
         String[] parts = br.readLine().split(" ");
         int v1 = Integer.parseInt(parts[0]);
         int v2 = Integer.parseInt(parts[1]);
         graph[v1].add(new Edge(v1, v2));
         graph[v2].add(new Edge(v2, v1));
      }

      int src = Integer.parseInt(br.readLine());
      int t = Integer.parseInt(br.readLine());
    
    boolean[] vis = new boolean[vtces];
    Queue<pair> q = new ArrayDeque<>();
    q.add(new pair(src, 1));
    int count=0;
    while(q.size()!=0){
        // remove
        pair rem = q.remove();
        
        if(vis[rem.src]) continue;
        vis[rem.src]=true; //mark
        if(rem.time>=t) break;
        
        for(Edge e : graph[rem.src]){
            if(!vis[e.nbr]){
                q.add(new pair(e.nbr, rem.time+1));
                count++;
            }
        }
    }
    System.out.println(count);
    
   }
   

}
