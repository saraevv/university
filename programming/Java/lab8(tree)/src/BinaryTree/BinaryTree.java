package BinaryTree;

public class BinaryTree<T extends Comparable<T>> {
    private class Node {
        private T value;
        private Node left;
        private Node right;

        public Node(T value) {
            this.value = value;
        }
    }

    private Node root;

    public boolean isEmpty() {
        return root == null;
    }

    public void add(T x) {
        Node node = new Node(x);
        //node.value = x;
        if (isEmpty())
            root = node;
        else {
            Node cur = root;
            Node prev = null;
            while (cur != null) {
                prev = cur;
                if (cur.value.compareTo(x) > 0) {
                    cur = cur.left;
                    if (cur == null)
                        prev.left = node;
                } else if (cur.value.compareTo(x) < 0) {
                    cur = cur.right;
                    if (cur == null)
                        prev.right = node;
                } else
                    return;
            }
        }
    }

    public boolean find(T x) {
        if (isEmpty())
            return false;
        else {
            Node cur = root;
            while (cur != null) {
                if (cur.value.compareTo(x) == 0)
                    return true;
                else if (cur.value.compareTo(x) > 0)
                    cur = cur.left;
                else if (cur.value.compareTo(x) < 0)
                    cur = cur.right;
            }
            return false;
        }
    }

    public void print(String str) {
        if (!isEmpty()) {
            switch (str) {
                case "preOrder":
                    preOrder(root);
                    break;
                case "inOrder":
                    inOrder(root);
                    break;
                case "postOrder":
                    postOrder(root);
            }
            System.out.println();
        }
    }

    private void preOrder(Node node) {
        if (node != null) {
            System.out.print(node.value + " ");
            preOrder(node.left);
            preOrder(node.right);
        }
    }

    private void inOrder(Node node) {
        if (node != null) {
            inOrder(node.left);
            System.out.print(node.value + " ");
            inOrder(node.right);
        }
    }

    private void postOrder(Node node) {
        if (node != null) {
            postOrder(node.left);
            postOrder(node.right);
            System.out.print(node.value + " ");
        }
    }

    public boolean delete(T x) {
        if (isEmpty())
            return false;
        else {
            Node cur = root, prev = null;
            boolean isleft = false;
            while (cur != null) {
                if (cur.value.compareTo(x) == 0) {
                    if (cur.left == null && cur.right == null) {
                        if (isleft)
                            prev.left = null;
                        else
                            prev.right = null;
                    } else if (cur.left == null) {
                        if (isleft)
                            prev.left = cur.right;
                        else
                            prev.right = cur.right;
                    } else if (cur.right == null) {
                        if (isleft)
                            prev.left = cur.left;
                        else
                            prev.right = cur.left;
                    } else {
                        Node min = cur.right;
                        prev = cur;
                        while (true) {
                            if (min.left == null)
                                break;
                            else {
                                prev = min;
                                min = min.left;
                            }
                        }
                        cur.value = min.value;
                        if (prev != cur)
                            prev.left = null;
                        else
                            prev.right = min.right;
                    }
                    return true;
                } else if (cur.value.compareTo(x) > 0) {
                    prev = cur;
                    cur = cur.left;
                    isleft = true;
                } else {
                    prev = cur;
                    cur = cur.right;
                    isleft = false;
                }
            }
            return false;
        }
    }
}
