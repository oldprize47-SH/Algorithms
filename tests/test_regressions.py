"""Compile coursework executables and check boundary/graph behaviour offline."""
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class CourseworkRegressionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.work = tempfile.TemporaryDirectory()
        cls.addClassCleanup(cls.work.cleanup)
        cls.programs = {}
        compiler = shutil.which("g++")
        if not compiler:
            raise RuntimeError("g++ is required to run these compile-and-execute tests")
        for hw in (3, 5):
            source = next(ROOT.glob(f"ALgorithm_HW{hw}_*.cpp"))
            executable = Path(cls.work.name) / f"hw{hw}.exe"
            subprocess.run([compiler, "-std=c++17", "-D_GLIBCXX_DEBUG", str(source),
                            "-o", str(executable)], check=True, capture_output=True, timeout=45)
            cls.programs[hw] = executable

    def run_hw(self, hw, data):
        return subprocess.run([str(self.programs[hw])], input=data, text=True,
                              capture_output=True, timeout=10)

    def test_zero_floors(self):
        result = self.run_hw(3, "0\n2\n")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Minimum Attempts (DP): 0", result.stdout)

    def test_regular_dp_case(self):
        result = self.run_hw(3, "10\n2\n")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Minimum Attempts (Recursive): 4", result.stdout)
        self.assertIn("Minimum Attempts (DP): 4", result.stdout)

    def test_cyclic_graph_has_no_topological_order(self):
        result = self.run_hw(5, "7\n")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("graph contains a cycle", result.stdout)
        self.assertNotIn("Topological Sort Result:", result.stdout)

    def test_dag_order_respects_edges(self):
        result = self.run_hw(5, "3\n")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Topological Sort Result:", result.stdout)
        order = re.findall(r"[A-C]", result.stdout.split("Topological Sort Result:")[1])
        self.assertEqual(order, ["A", "B", "C"])

    def test_invalid_graph_sizes_are_rejected(self):
        for value in ("0", "11", "bad"):
            with self.subTest(value=value):
                result = self.run_hw(5, value + "\n")
                self.assertNotEqual(result.returncode, 0)
                self.assertIn("number of nodes must be between 1 and 10", result.stdout)


if __name__ == "__main__":
    unittest.main()
