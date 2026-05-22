template<typename T, int N>
struct StaticVector {
    T    data[N];
    int  count = 0;

    void push_back(const T& val){ if(count < N) data[count++] = val; }
    void clear(){ count = 0; }
    int  size() const { return count; }
    T&   operator[](int i){ return data[i]; }
    const T& operator[](int i) const { return data[i]; }

    T* begin(){ return data; }
    T* end()  { return data + count; }
};
