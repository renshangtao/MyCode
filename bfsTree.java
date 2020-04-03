import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

//给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。
//        示例：
//        二叉树：[3,9,20,null,null,15,7],
//
//        3
//        / \
//        9  20
//        /  \
//        15   7
//        返回其层次遍历结果：
//
//        [
//        [3],
//        [9,20],
//        [15,7]
//        ]
//

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}


public class bfsTree {

    //  递归法，难点，如果确定这是第几层，下面解决方法是传入一个参数，
    //  在Java近乎流氓的方法get(level）可以轻松拿到对应的层，对于C语言来说简直是噩梦
//    List<List<Integer>> levels = new ArrayList<List<Integer>>();
//
//    void order(TreeNode tn, int level)
//    {
//        if (tn == null)
//            return;
//
//        if (levels.size() == level)
//            levels.add(new ArrayList<Integer>());
//
//        levels.get(level).add(tn.val);
//
//        order(tn.left, level+1);
//        order(tn.right, level+1);
//    }

    List<List<Integer>> levels = new ArrayList<List<Integer>>();

    public List<List<Integer>> levelOrder(TreeNode root)
    {
        //order(root, 0);

        //为空，直接返回
        if (root == null)
            return levels;

        //利用队列先进先出的特性，一层层遍历，BFS，广度优先搜索
        //这儿的难点是，如何分出层来，下面给出了一个好方法，将每个使用的节点移除掉，这样里面剩下的都是本层的。
        int level = 0;
        Queue<TreeNode> qt = new LinkedList<TreeNode>();
        qt.add(root);

        while (qt.size() > 0)
        {
            levels.add(new ArrayList<Integer>());

            int level_size = qt.size();
            for (int i = 0; i < level_size; i++)
            {
                TreeNode tn = qt.remove();
                levels.get(level).add(tn.val);

                if (tn.left != null) qt.add(tn.left);
                if (tn.right != null) qt.add(tn.right);
            }

            level++;
        }

        return levels;
    }
}
