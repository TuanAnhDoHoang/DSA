`Cây AVL là cây cân bằng, tính chất này duy trì mọi thời điểm`

**Xét cây AVL có n nút, độ cao h, gốc là node cao nhất (h root = 0)**: 
Các thao tác xây dựng:
  Thêm một nút vào cây - cân bằng lại
  Xoá một nút khỏi cây - cân bằng lại
  In các nút trên cây theo độ cao, từ trái sang phải (độ cao 0 -> h-1)


Breakdown code: 
1. Tạo class node chứa thuộc tính: dữ liệu (nút 5, nút 6, ...), nút con trái, nút con phải, chiều cao của nút tính từ gốc; Tạo hàm khởi tạo (Node)

`class Node{
    public:
        int value;
        Node* left;
        Node* right;
        int height;
        Node(int data){
            this->value = data;
            left = NULL;
            right = NULL;
            height = 1;
        }
};
`

2.Xây dựng class cây AVL và một số chức năng (thêm node, xoá node, xoay cây, tính hệ số cân bằng, tính chiều cao của một node, In các node trên cây theo độ cao từ trái->phải)

a) Hàm lấy chiều cao:

`
 int getHeight(Node* x){
        if(x == NULL)return 0;
        return x->height;
    }
`
*Chiều cao một node tính bằng độ sâu của **cây con** tại node đó*
Ví dụ: node lá có chiều cao là 1, cha của node lá có chiều cao là 2, cha của cha node lá có chiều cao là 3, vv


b) Hàm lấy hệ số cân bằng:

`
 int getBalance(Node* currNode){
        if(currNode == NULL)return maxn;
        Node* left = currNode->left;
        Node* right = currNode->right;

        if(left != NULL && right != NULL){
            return left->height - right->height;
        }
        else if(left == NULL && right == NULL) return 0;
        else if(left == NULL) return 0 - right->height;
        return left->height;
    }
`

*Hệ số cân bằng = Chiều cao cây con trái (lấy nút trái đại diện)  - chiều cao cây con phải(lấy nút phải đại diện)*
 Kết quả có các trường hợp: bằng 0, >= 1 hoặc <=-1
    0 : khi chiều cao trái phải bằng nhau
    >= 1 : khi trái cao hơn phải
    <= -1: khi phải cao hơn trái

**Hệ số cân bằng là mấu chốt để xác định cây nghiên như thế nào**

c) Hàm xoay trái
`
Node* L_rotate(Node* x){
        Node* r_x = x->right;
        Node* temp = r_x->left;

        r_x->left = x;
        x->right = temp;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        r_x->height = 1 + max(getHeight(x->left), getHeight(x->right));

       return r_x; 
    }
`
Thuật toán xoay trái cơ bản là: 
  Ta xét cần xoay trái tại nút x:
  - ta có con phải của x là right_x (trong code là r_x)
  - lưu con trái của right_x là temp
  - Cho cha của x nối vào right_x (cho x cút) (bước này không thể hiện trong hàm, mà là khi trả về)
  - Cho x là con trái của right_x (con phải của x)
  - Gắn bên trái của right_x (temp) vào con phải của x 
  -> Sau tất cả, ta thu được : cha của x -> right_x ;  Bên trái của right_x là x, bên phải của x là temp (con trái của right_x)

<img src="https://media.geeksforgeeks.org/wp-content/uploads/20221229131815/avl11-(1)-768.png"> 
   

d) Tương tự với xoay phải

**Từ đây là các thao tác chính**
I) Hàm push (thêm một node - cân bằng cây) : push(int data)
*Định nghĩa:*
  Node đang xét : currNode
  Giá trị của node : currNode -> value

- Việc thêm giống như cây binary search tree, ta đi từ gốc xuống, so sánh giữa data (giá trị ta muốn thêm ) với các giá trị node mà ta gặp, sẽ có 4 trường hợp: 
  + data > currNode->value : Ta duyệt xuống cây con phải (currNode = currNode->right)
  + data < currNode->value : Ta duyệt xuống cây con trái (currNode = currNode->left)
  + data == value :  đã tồn tại, và không thể thêm được -> thoát 
  + currNode == NULL : vị trí trống - có thể thêm node mới của ta tại đây (currNode = new node() )
  
- Sau khi thêm xong, ta cần cập nhật lại chiều cao: 
  chiều cao = 1 + max( chiều cao cây con phải , chiều cao cây con trái)

- *Cân bằng cây*
Step 1: tính hệ số cân bằng (gọi hàm getBalance())
`
int balance = getBalance(currNode);
`
Step 2: xét hệ số cân bằng
*Một nút cân bằng khi hệ số cân bằng của nó thuộc [-1;1]*
*Một nút mất cân bằng khi hệ số cân bằng của nó > 1 hoặc < -1*
 
  Gọi nút mất cân bằng là 
  Nếu hệ số cân bằng lớn hơn 1: 
    Ta chia thêm 2 trường hợp nhỏ: 
      Nút ta mới thêm có giá trị lớn hơn x: nghiên trái - phải
      Nút ta mới thêm có giá trị nhỏ hơn x: nghiên trái - trái

      
  Nếu hệ số cân bằng nhỏ hơn -1:
    Ta chia thêm 2 trường hợp nhỏ: 
      Nút ta mới thêm có giá trị lớn hơn x: nghiên phải - phải
      Nút ta mới thêm có giá trị nhỏ hơn x: nghiên phải - trái
Step 3:
  Sau khi xác định được cây con đó nghiên thế nào thì ta thực hiện xoay theo trường hợp
  1) Nghiên trái trái : xoay phải
  2) Nghiên phải phải : xoay trái
  3) Nghiên trái phải : xoay trái tại nút con trái của x, rồi xoay phải tại x
  4) Nghiên phải trái : xoay phải tại nút con phải của x, rồi xoay trái tại x

`
if(currNode->left != NULL){
    if(balance > 1 && data < currNode->left->value){
        return R_rotate(currNode);
    }
    if(balance > 1 && data > currNode->left->value){
        currNode->left = L_rotate(currNode->left); 
        return R_rotate(currNode);
    }
}
if(currNode->right != NULL){
    if(balance < -1 && data > currNode->right->value){
        return L_rotate(currNode);
    }
    if(balance < -1 && data < currNode->right->value){
        currNode->right = R_rotate(currNode->right);
        return L_rotate(currNode);
    }
}
`
**Ta Hoàn thành việc thêm 1 node và cân bằng lại cây**
