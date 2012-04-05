import unittest
import math

from pyglm import *

# Note that because assertAlmostEqual uses absolute error, we need to increase
# the tolerance of bigger numbers, such as 90 as compared to 1e-7.
# This is why you'll see tolerances of 1e-4 when we work with degrees.

class TestQuaternion(unittest.TestCase):

    def test_ctor(self):
        q = Quaternion()
        self.assertEqual(q.x, 0.0)
        self.assertEqual(q.y, 0.0)
        self.assertEqual(q.z, 0.0)
        self.assertEqual(q.w, 1.0)

    def test_ctor3(self):
        q = Quaternion(1.0, 2.0, 3.0)
        self.assertEqual(q.x, 1.0)
        self.assertEqual(q.y, 2.0)
        self.assertEqual(q.z, 3.0)
        self.assertEqual(q.w, 1.0)

    def test_ctor4(self):
        q = Quaternion(1.0, 2.0, 3.0, 4.0)
        self.assertEqual(q.x, 1.0)
        self.assertEqual(q.y, 2.0)
        self.assertEqual(q.z, 3.0)
        self.assertEqual(q.w, 4.0)

    def test_ctor_iterable(self):
        q = Quaternion(range(4))
        self.assertEqual(q.x, 0.0)
        self.assertEqual(q.y, 1.0)
        self.assertEqual(q.z, 2.0)
        self.assertEqual(q.w, 3.0)

        q = Quaternion([0.1, 0.2])
        self.assertAlmostEqual(q.x, 0.1, 6)
        self.assertAlmostEqual(q.y, 0.2, 6)
        self.assertEqual(q.z, 0.0)
        self.assertEqual(q.w, 1.0)

        q = Quaternion((0.1, 0.2))
        self.assertAlmostEqual(q.x, 0.1, 6)
        self.assertAlmostEqual(q.y, 0.2, 6)
        self.assertEqual(q.z, 0.0)
        self.assertEqual(q.w, 1.0)

    def test_ctor_rotation(self):
        q1 = Quaternion(axis=(0.0, 1.0, 0.0), angle=math.radians(90))
        q2 = Quaternion(axis=(0.0, 1.0, 0.0), radians=math.radians(90))
        q3 = Quaternion(axis=(0.0, 1.0, 0.0), degrees=90)
        q4 = Quaternion(axis=Vector(0.0, 1.0, 0.0), angle=math.radians(90))
        q5 = Quaternion(axis=Vector(0.0, 1.0, 0.0), radians=math.radians(90))
        q6 = Quaternion(axis=Vector(0.0, 1.0, 0.0), degrees=90)
        q7 = Quaternion((0.0, 1.0, 0.0), angle=math.radians(90))
        q8 = Quaternion((0.0, 1.0, 0.0), radians=math.radians(90))
        q9 = Quaternion((0.0, 1.0, 0.0), degrees=90)
        q10= Quaternion((0.0, 1.0, 0.0), math.radians(90))
        q11= Quaternion(Vector(0.0, 1.0, 0.0), angle=math.radians(90))
        q12= Quaternion(Vector(0.0, 1.0, 0.0), radians=math.radians(90))
        q13= Quaternion(Vector(0.0, 1.0, 0.0), degrees=90)
        q14= Quaternion(Vector(0.0, 1.0, 0.0), math.radians(90))

        self.assertEqual(q1, q2)
        self.assertEqual(q1, q3)
        self.assertEqual(q1, q4)
        self.assertEqual(q1, q5)
        self.assertEqual(q1, q6)
        self.assertEqual(q1, q7)
        self.assertEqual(q1, q8)
        self.assertEqual(q1, q9)
        self.assertEqual(q1, q10)
        self.assertEqual(q1, q11)
        self.assertEqual(q1, q12)
        self.assertEqual(q1, q13)
        self.assertEqual(q1, q14)

        self.assertAlmostEqual(q1.axis, Vector(0.0, 1.0, 0.0), 6)
        self.assertAlmostEqual(q1.angle, math.radians(90), 6)

    def test_ctor_named(self):
        q1 = rotQ(axis=(0.0, 1.0, 0.0), angle=math.radians(90))
        q2 = rotQ(axis=(0.0, 1.0, 0.0), radians=math.radians(90))
        q3 = rotQ(axis=(0.0, 1.0, 0.0), degrees=90)
        q4 = rotQ(axis=Vector(0.0, 1.0, 0.0), angle=math.radians(90))
        q5 = rotQ(axis=Vector(0.0, 1.0, 0.0), radians=math.radians(90))
        q6 = rotQ(axis=Vector(0.0, 1.0, 0.0), degrees=90)
        q7 = rotQ(0.0, 1.0, 0.0, angle=math.radians(90))
        q8 = rotQ(0.0, 1.0, 0.0, radians=math.radians(90))
        q9 = rotQ(0.0, 1.0, 0.0, degrees=90)
        q10= rotQ(0.0, 1.0, 0.0, math.radians(90))
        q11= rotQ(Vector(0.0, 1.0, 0.0), angle=math.radians(90))
        q12= rotQ(Vector(0.0, 1.0, 0.0), radians=math.radians(90))
        q13= rotQ(Vector(0.0, 1.0, 0.0), degrees=90)
        q14= rotQ(Vector(0.0, 1.0, 0.0), math.radians(90))

        self.assertEqual(q1, q2)
        self.assertEqual(q1, q3)
        self.assertEqual(q1, q4)
        self.assertEqual(q1, q5)
        self.assertEqual(q1, q6)
        self.assertEqual(q1, q7)
        self.assertEqual(q1, q8)
        self.assertEqual(q1, q9)
        self.assertEqual(q1, q10)
        self.assertEqual(q1, q11)
        self.assertEqual(q1, q12)
        self.assertEqual(q1, q13)
        self.assertEqual(q1, q14)

        self.assertAlmostEqual(q1.axis, Vector(0.0, 1.0, 0.0), 6)
        self.assertAlmostEqual(q1.angle, math.radians(90), 6)

    def test_ctor_bad(self):
        with self.assertRaises(ValueError):
            q = Quaternion(1.0)
        with self.assertRaises(ValueError):
            q = Quaternion(1.0, 2.0, 3.0, 4.0, 5.0)

    def test_axis_angle_getter(self):
        q = Quaternion(1.0, 0.0, 0.0, math.cos(0.5*math.radians(90)))
        self.assertAlmostEqual(q.axis, Vector(1.0, 0.0, 0.0), 6)
        self.assertAlmostEqual(q.angle, math.radians(90), 6)
        self.assertAlmostEqual(q.radians, math.radians(90), 6)
        self.assertAlmostEqual(q.rad, math.radians(90), 6)
        self.assertAlmostEqual(q.degrees, 90, 4)
        self.assertAlmostEqual(q.deg, 90, 4)

    def test_getter_bad(self):
        q = Quaternion()
        with self.assertRaises(AttributeError):
            q.q

    def test_setter(self):
        q = Quaternion()
        q.x = 0.1
        q.y = 0.2
        q.z = 0.3
        q.w = 0.4
        self.assertAlmostEqual(q.x, 0.1)
        self.assertAlmostEqual(q.y, 0.2)
        self.assertAlmostEqual(q.z, 0.3)
        self.assertAlmostEqual(q.w, 0.4)

    def test_axis_setter1(self):
        q = Quaternion(1, 1, 1, math.cos(0.5*0.1))
        q.axis = Vector(0,1,0)
        self.assertAlmostEqual(q.axis.x, 0)
        self.assertAlmostEqual(q.axis.y, 1)
        self.assertAlmostEqual(q.axis.z, 0)
        self.assertAlmostEqual(q.angle, 0.1, 6)

    def test_axis_setter2(self):
        q = Quaternion(1, 1, 1, math.cos(0.5*0.1))
        q.axis = (0,1,0)
        self.assertAlmostEqual(q.axis.x, 0)
        self.assertAlmostEqual(q.axis.y, 1)
        self.assertAlmostEqual(q.axis.z, 0)
        self.assertAlmostEqual(q.angle, 0.1, 6)

    def test_angle_setter1(self):
        q = Quaternion()
        q.angle = 0.5
        self.assertAlmostEqual(q.angle, 0.5, 6)
        self.assertAlmostEqual(q.radians, 0.5, 6)
        self.assertAlmostEqual(q.rad, 0.5, 6)
        self.assertAlmostEqual(q.degrees, math.degrees(0.5), 4)
        self.assertAlmostEqual(q.deg, math.degrees(0.5), 4)

    def test_angle_setter2(self):
        q = Quaternion()
        q.rad = 0.5
        self.assertAlmostEqual(q.angle, 0.5, 6)
        self.assertAlmostEqual(q.radians, 0.5, 6)
        self.assertAlmostEqual(q.rad, 0.5, 6)
        self.assertAlmostEqual(q.degrees, math.degrees(0.5), 4)
        self.assertAlmostEqual(q.deg, math.degrees(0.5), 4)

    def test_angle_setter3(self):
        q = Quaternion()
        q.radians = 0.5
        self.assertAlmostEqual(q.angle, 0.5, 6)
        self.assertAlmostEqual(q.radians, 0.5, 6)
        self.assertAlmostEqual(q.rad, 0.5, 6)
        self.assertAlmostEqual(q.degrees, math.degrees(0.5), 4)
        self.assertAlmostEqual(q.deg, math.degrees(0.5), 4)

    def test_angle_setter4(self):
        q = Quaternion()
        q.deg = 90
        self.assertAlmostEqual(q.angle, math.radians(90), 6)
        self.assertAlmostEqual(q.radians, math.radians(90), 6)
        self.assertAlmostEqual(q.rad, math.radians(90), 6)
        self.assertAlmostEqual(q.degrees, 90, 4)
        self.assertAlmostEqual(q.deg, 90, 4)

    def test_angle_setter5(self):
        q = Quaternion()
        q.degrees = 90
        self.assertAlmostEqual(q.angle, math.radians(90), 4)
        self.assertAlmostEqual(q.radians, math.radians(90), 4)
        self.assertAlmostEqual(q.rad, math.radians(90), 4)
        self.assertAlmostEqual(q.degrees, 90, 4)
        self.assertAlmostEqual(q.deg, 90, 4)

    def test_setter_bad(self):
        q = Quaternion()
        with self.assertRaises(AttributeError):
            q.q = 3.0
        with self.assertRaises(ValueError):
            q.x = "abc"

    def test_comparison(self):
        q1 = Quaternion(1, 2, 3, 4)
        q2 = Quaternion(4, 3, 2, 1)
        q3 = Quaternion(1, 0, -1, 0)
        q1b = Quaternion(1, 2, 3, 4)

        self.assertTrue(q1 == q1b)
        self.assertTrue(q1 >= q1b)
        self.assertTrue(q1 <= q1b)
        self.assertFalse(q1 != q1b)
        self.assertFalse(q1 < q1b)
        self.assertFalse(q1 > q1b)

        self.assertTrue(q1 != q2)
        self.assertTrue(q1 >= q2)
        self.assertTrue(q1 <= q2)
        self.assertFalse(q1 == q2)
        self.assertFalse(q1 < q2)
        self.assertFalse(q1 > q2)

        self.assertTrue(q1 != q3)
        self.assertTrue(q1 >= q3)
        self.assertTrue(q1 > q3)
        self.assertFalse(q1 == q3)
        self.assertFalse(q1 <= q3)
        self.assertFalse(q1 < q3)

    def test_comparison_bad(self):
        with self.assertRaises(TypeError):
            Quaternion() == 3
        with self.assertRaises(TypeError):
            3 == Quaternion()
        with self.assertRaises(TypeError):
            Quaternion() == "1,2,3,4"
        with self.assertRaises(TypeError):
            "1,2,3,4" == Quaternion()

    def test_negation(self):
        q = Quaternion(1, 0, 2, -1)
        mq = -q
        self.assertAlmostEqual(mq.x, -q.x, 6)
        self.assertAlmostEqual(mq.y, -q.y, 6)
        self.assertAlmostEqual(mq.z, -q.z, 6)
        self.assertAlmostEqual(mq.w, -q.w, 6)

        self.assertEqual(-mq, q)

    def test_addition(self):
        q1 = Quaternion(1, 2, 3, 4)
        q2 = Quaternion(0.1, 0.2, 0.3, 0.4)
        q12 = q1 + q2
        self.assertAlmostEqual(q12.x, q1.x + q2.x, 6)
        self.assertAlmostEqual(q12.y, q1.y + q2.y, 6)
        self.assertAlmostEqual(q12.z, q1.z + q2.z, 6)
        self.assertAlmostEqual(q12.w, q1.w + q2.w, 6)

    def test_addition_bad(self):
        with self.assertRaises(TypeError):
            Quaternion() + 1
        with self.assertRaises(TypeError):
            Quaternion() + "1,2,3,4"

    @unittest.skip("Currently, this crashes python. Why? Probably because numeric_int etc. are missing.")
    def test_addition_bad2(self):
        with self.assertRaises(TypeError):
            1 + Quaternion()
        with self.assertRaises(TypeError):
            "1,2,3,4" + Quaternion()

    def test_subtraction(self):
        q1 = Quaternion(1, 2, 3, 4)
        q2 = Quaternion(0.1, 0.2, 0.3, 0.4)
        q12 = q1 - q2
        self.assertAlmostEqual(q12.x, q1.x - q2.x, 6)
        self.assertAlmostEqual(q12.y, q1.y - q2.y, 6)
        self.assertAlmostEqual(q12.z, q1.z - q2.z, 6)
        self.assertAlmostEqual(q12.w, q1.w - q2.w, 6)

    def test_subtraction_bad(self):
        with self.assertRaises(TypeError):
            Quaternion() - 1
        with self.assertRaises(TypeError):
            Quaternion() - "1,2,3,4"

    @unittest.skip("Currently, this crashes python. Why? Probably because numeric_int etc. are missing.")
    def test_subtraction_bad2(self):
        with self.assertRaises(TypeError):
            1 - Quaternion()
        with self.assertRaises(TypeError):
            "1,2,3,4" - Quaternion()

    def test_scaling(self):
        q1 = Quaternion(1, 2, 5, 10)
        f = 0.5
        q1f = q1*f
        self.assertAlmostEqual(q1f.x, q1.x*f, 6)
        self.assertAlmostEqual(q1f.y, q1.y*f, 6)
        self.assertAlmostEqual(q1f.z, q1.z*f, 6)
        self.assertAlmostEqual(q1f.w, q1.w*f, 6)

    def test_scaling_bad(self):
        with self.assertRaises(TypeError):
            Quaternion() * "1,2,3,4"

#    def test_concatenation(self):
#        q1 = Quaternion(1.0, 0.0, 0.0, )

    @unittest.skip("Currently, this crashes python. Why? Probably because numeric_int etc. are missing.")
    def test_scaling_bad2(self):
        with self.assertRaises(TypeError):
            "1,2,3,4" + Quaternion()

    def test_dot(self):
        qx = Quaternion(1, 0, 0, 0)
        qy = Quaternion(0, 1, 0, 0)
        qz = Quaternion(0, 0, 1, 0)
        qw = Quaternion(0, 0, 0, 1)

        self.assertAlmostEqual(qx.dot(qy), 0, 6)
        self.assertAlmostEqual(qy.dot(qx), 0, 6)
        self.assertAlmostEqual(qx.dot(qz), 0, 6)
        self.assertAlmostEqual(qz.dot(qx), 0, 6)
        self.assertAlmostEqual(qx.dot(qw), 0, 6)
        self.assertAlmostEqual(qw.dot(qx), 0, 6)
        self.assertAlmostEqual(qy.dot(qz), 0, 6)
        self.assertAlmostEqual(qz.dot(qy), 0, 6)
        self.assertAlmostEqual(qy.dot(qw), 0, 6)
        self.assertAlmostEqual(qw.dot(qy), 0, 6)
        self.assertAlmostEqual(qz.dot(qw), 0, 6)
        self.assertAlmostEqual(qw.dot(qz), 0, 6)
        self.assertAlmostEqual(qx.dot(qx), 1, 6)
        self.assertAlmostEqual(qy.dot(qy), 1, 6)
        self.assertAlmostEqual(qz.dot(qz), 1, 6)
        self.assertAlmostEqual(qw.dot(qw), 1, 6)

        self.assertAlmostEqual(Quaternion(10,20,50, 100).dot(Quaternion(0.1, 0.05, 0.02, 0.01)), 4, 6)

    def test_dot_bad(self):
        with self.assertRaises(TypeError):
            Quaternion().dot()
        with self.assertRaises(TypeError):
            Quaternion().dot("Hi")
        with self.assertRaises(TypeError):
            Quaternion().dot(3)

    def test_len(self):
        q1 = Quaternion(1, 0, 0, 0)
        q4 = Quaternion(1, 1, 1, 1)

        self.assertAlmostEqual(q1.len(), 1, 6)
        self.assertAlmostEqual(q4.len(), math.sqrt(4), 6)

    def test_len_bad(self):
        with self.assertRaises(TypeError):
            Quaternion().len(32)

    def test_normalize(self):
        q = Quaternion(1, 1, 1, 1)
        q.normalize()
        self.assertAlmostEqual(q.len(), 1, 6)

    def test_normalize_bad(self):
        with self.assertRaises(TypeError):
            Quaternion().normalize(32)

    def test_normalized(self):
        q = Quaternion(1, 1, 1, 1)
        qn = q.normalized()
        self.assertAlmostEqual(qn.len(), 1, 6)
        self.assertEqual(q, Quaternion(1, 1, 1, 1))

    def test_normalized_bad(self):
        with self.assertRaises(TypeError):
            Quaternion().normalized(32)

if __name__ == '__main__':
    unittest.main()

