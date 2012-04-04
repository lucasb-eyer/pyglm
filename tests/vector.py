import unittest

from pyglm import *

class TestVector(unittest.TestCase):

    def test_ctor(self):
        v = Vector()
        self.assertEqual(v.x, 0.0)
        self.assertEqual(v.y, 0.0)
        self.assertEqual(v.z, 0.0)

    def test_ctor2(self):
        v = Vector(1.0, 2.0)
        self.assertEqual(v.x, 1.0)
        self.assertEqual(v.y, 2.0)
        self.assertEqual(v.z, 0.0)

    def test_ctor3(self):
        v = Vector(1.0, 2.0, 3.0)
        self.assertEqual(v.x, 1.0)
        self.assertEqual(v.y, 2.0)
        self.assertEqual(v.z, 3.0)

    def test_ctor_iterable(self):
        v = Vector(range(3))
        self.assertEqual(v.x, 0.0)
        self.assertEqual(v.y, 1.0)
        self.assertEqual(v.z, 2.0)

        v = Vector([0.1, 0.2])
        self.assertAlmostEqual(v.x, 0.1, 6)
        self.assertAlmostEqual(v.y, 0.2, 6)
        self.assertAlmostEqual(v.z, 0.0, 6)

        v = Vector((0.1, 0.2))
        self.assertAlmostEqual(v.x, 0.1, 6)
        self.assertAlmostEqual(v.y, 0.2, 6)
        self.assertAlmostEqual(v.z, 0.0, 6)

    def test_ctor_bad(self):
        with self.assertRaises(ValueError):
            v = Vector(1.0)
        with self.assertRaises(ValueError):
            v = Vector(1.0, 2.0, 3.0, 4.0, 5.0)

    def test_setter(self):
        v = Vector()
        v.x = 0.1
        v.y = 0.2
        v.z = 0.3
        self.assertAlmostEqual(v.x, 0.1)
        self.assertAlmostEqual(v.y, 0.2)
        self.assertAlmostEqual(v.z, 0.3)

    def test_getter_bad(self):
        v = Vector()
        with self.assertRaises(AttributeError):
            v.w

    def test_setter_bad(self):
        v = Vector()
        with self.assertRaises(AttributeError):
            v.w = 3.0

    def test_comparison(self):
        v1 = Vector(1, 2, 3)
        v2 = Vector(3, 2, 1)
        v3 = Vector(1, 0, -1)
        v1b = Vector(1, 2, 3)

        self.assertTrue(v1 == v1b)
        self.assertTrue(v1 >= v1b)
        self.assertTrue(v1 <= v1b)
        self.assertFalse(v1 != v1b)
        self.assertFalse(v1 < v1b)
        self.assertFalse(v1 > v1b)

        self.assertTrue(v1 != v2)
        self.assertTrue(v1 >= v2)
        self.assertTrue(v1 <= v2)
        self.assertFalse(v1 == v2)
        self.assertFalse(v1 < v2)
        self.assertFalse(v1 > v2)

        self.assertTrue(v1 != v3)
        self.assertTrue(v1 >= v3)
        self.assertTrue(v1 > v3)
        self.assertFalse(v1 == v3)
        self.assertFalse(v1 <= v3)
        self.assertFalse(v1 < v3)

    def test_negation(self):
        v = -Vector(1, 0, 2)
        self.assertAlmostEqual(v.x, -1, 6)
        self.assertAlmostEqual(v.y, 0, 6)
        self.assertAlmostEqual(v.z, -2, 6)

        self.assertEqual(-v, Vector(1, 0, 2))

    def test_addition(self):
        v1 = Vector(1, 2, 3)
        v2 = Vector(0.1, 0.2, 0.3)
        v12 = v1 + v2
        self.assertAlmostEqual(v12.x, v1.x + v2.x, 6)
        self.assertAlmostEqual(v12.y, v1.y + v2.y, 6)
        self.assertAlmostEqual(v12.z, v1.z + v2.z, 6)

    def test_subtraction(self):
        v1 = Vector(1, 2, 3)
        v2 = Vector(0.1, 0.2, 0.3)
        v12 = v1 - v2
        self.assertAlmostEqual(v12.x, v1.x - v2.x, 6)
        self.assertAlmostEqual(v12.y, v1.y - v2.y, 6)
        self.assertAlmostEqual(v12.z, v1.z - v2.z, 6)

    def test_scaling(self):
        v1 = Vector(1, 2, 3)
        f = 0.5
        v1f = v1*f
        self.assertAlmostEqual(v1f.x, v1.x*f, 6)
        self.assertAlmostEqual(v1f.y, v1.y*f, 6)
        self.assertAlmostEqual(v1f.z, v1.z*f, 6)

    def test_no_multiplication(self):
        with self.assertRaises(TypeError):
            Vector() * Vector()

    def test_cross(self):
        vx = Vector(1, 0, 0)
        vy = Vector(0, 1, 0)
        vz = Vector(0, 0, 1)

        self.assertEqual(vx.cross(vy), vz)
        self.assertEqual(vy.cross(vz), vx)
        self.assertEqual(vz.cross(vx), vy)
        self.assertEqual(vy.cross(vx), -vz)
        self.assertEqual(vz.cross(vy), -vx)
        self.assertEqual(vx.cross(vz), -vy)

    def test_dot(self):
        vx = Vector(1, 0, 0)
        vy = Vector(0, 1, 0)
        vz = Vector(0, 0, 1)

        self.assertAlmostEqual(vx.dot(vy), 0)
        self.assertAlmostEqual(vy.dot(vx), 0)
        self.assertAlmostEqual(vx.dot(vz), 0)
        self.assertAlmostEqual(vz.dot(vx), 0)
        self.assertAlmostEqual(vy.dot(vz), 0)
        self.assertAlmostEqual(vz.dot(vy), 0)
        self.assertAlmostEqual(vx.dot(vx), 1)
        self.assertAlmostEqual(vy.dot(vy), 1)
        self.assertAlmostEqual(vz.dot(vz), 1)

        self.assertAlmostEqual(Vector(10,20,50).dot(Vector(0.1, 0.05, 0.02)), 3)

if __name__ == '__main__':
    unittest.main()

