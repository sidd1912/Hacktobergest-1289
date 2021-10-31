import java.util.*;

class Main {
    public static Scanner scn = new Scanner(System.in);

    public static class ListNode {
        int val = 0;
        boolean vis = false;
        ListNode next = null;

        ListNode(int val, boolean vis) {
            this.val = val;
            this.vis = vis;
        }
    }

    public static boolean isCyclePresentInLL(ListNode head) {
        if(head==null) return false;
        ListNode temp = head;
        while(temp!=null && temp.vis==false){
            temp.vis=true;
            temp=temp.next;
        }
        if(temp==null) return false;
        if(temp.vis) return true;

        return false;
    }

    public static ListNode takeInput() {
        int n = scn.nextInt();
        ListNode dummy = new ListNode(-1,false);
        ListNode prev = dummy;
        while (n-- > 0) {
            prev.next = new ListNode(scn.nextInt(),false);
            prev = prev.next;
        }
        int idx = scn.nextInt();
        if (idx >= 0) {
            ListNode curr = dummy.next;
            while (idx-- > 0) {
                curr = curr.next;
            }
            prev.next = curr;
        }
        return dummy.next;
    }

    public static void main(String[] args) {
        ListNode head = takeInput();
        System.out.println(isCyclePresentInLL(head));
    }
}
