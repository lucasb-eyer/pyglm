template<class T>
T& operator<<(T& f, const Vector& v) {
    return f << v.x() << v.y() << v.z();
}

template<class T>
T& operator>>(T& f, Vector& v) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    f >> x >> y >> z;
    v.x(x).y(y).z(z);
    return f;
}

