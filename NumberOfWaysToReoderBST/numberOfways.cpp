#include <iostream>
using namespace std;

#define MOD 1000000007

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

typedef long long ll;

ll fact[1001];
ll ans = 1;

void precalc() {
    fact[0] = 1;
    for (ll i = 1; i < 1001; i++)
        fact[i] = (fact[i - 1] * i) % MOD;
}

ll inv(ll x) {
    return x <= 1 ? x : MOD - (MOD / x) * inv(MOD % x) % MOD;
}

ll mul(ll x, ll y) {
    return ((x % MOD) * 1ll * (y % MOD)) % MOD;
}

ll divide(ll x, ll y) {
    return mul(x, inv(y));
}

Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insertBST(Node* root, int val) {
    if (root->value > val) {
        if (root->left == NULL) {
            root->left = createNode(val);
        } else {
            insertBST(root->left, val);
        }
    } else if (root->value < val) {
        if (root->right == NULL) {
            root->right = createNode(val);
        } else {
            insertBST(root->right, val);
        }
    }
}

ll compute(ll left, ll right) {
    if (left == 0 || right == 0) return 1LL;
    return divide(fact[left + right], mul(fact[left], fact[right]));
}

ll calculatePermutations(Node* root) {
    if (root == NULL) {
        return 0;
    }

    ll left = calculatePermutations(root->left);
    ll right = calculatePermutations(root->right);
    ll pnc = compute(left, right) % MOD;
    ans = mul(ans, pnc);
    return 1 + left + right;
}

int numOfWays(int nums[], int n) {
    Node* root = createNode(nums[0]);

    // Create BST
    for (int i = 1; i < n; i++) {
        insertBST(root, nums[i]);
    }

    precalc(); // Precalculating the factorial till 1000
    calculatePermutations(root);
    return (int)(ans - 1);
}

int main() {
    int n;
    cin >> n;

    int nums[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int result = numOfWays(nums, n);
    cout << result << endl;

    return 0;
}
