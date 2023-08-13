#include <gtest/gtest.h>

#include <cmath>
#include <vector>

#include "../src/model/figure.h"
#include "../src/model/file_reader.h"
#include "../src/model/scene.h"
#include "../src/model/transform_matrix_builder.h"

constexpr double kEps = 10e-6;

s21::Figure CreateCube() {
  s21::Figure cube;
  cube.AddVertex(s21::Point3D(-0.5, -0.5, 0.5));
  cube.AddVertex(s21::Point3D(0.5, -0.5, 0.5));
  cube.AddVertex(s21::Point3D(-0.5, 0.5, 0.5));
  cube.AddVertex(s21::Point3D(0.5, 0.5, 0.5));
  cube.AddVertex(s21::Point3D(-0.5, 0.5, -0.5));
  cube.AddVertex(s21::Point3D(0.5, 0.5, -0.5));
  cube.AddVertex(s21::Point3D(-0.5, -0.5, -0.5));
  cube.AddVertex(s21::Point3D(0.5, -0.5, -0.5));
  return cube;
}

void compare_coordinates(const std::vector<s21::Vertex>& vertices,
                         const std::vector<double>& expected_values) {
  int i = -1;
  for (auto& vertex : vertices) {
    EXPECT_DOUBLE_EQ(vertex.GetPosition().x, expected_values[++i]);
    EXPECT_DOUBLE_EQ(vertex.GetPosition().y, expected_values[++i]);
    EXPECT_DOUBLE_EQ(vertex.GetPosition().z, expected_values[++i]);
  }
}

void compare_indices(const std::vector<s21::Edge>& edges,
                     const std::vector<unsigned int>& expected_values) {
  int i = -1;
  for (auto& edge : edges) {
    EXPECT_EQ(edge.GetBeginVertex(), expected_values[++i]);
    EXPECT_EQ(edge.GetEndVertex(), expected_values[++i]);
  }
}

TEST(ScaleTest, HandlesPositiveInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateScaleMatrix(2.0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -1.0, -1.0, 1.0,  1.0, -1.0, 1.0,  -1.0, 1.0,  1.0,  1.0, 1.0,  1.0,
      -1.0, 1.0,  -1.0, 1.0, 1.0,  -1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(ScaleTest, HandlesNegativeInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateScaleMatrix(-2.0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      1.0, 1.0,  -1.0, -1.0, 1.0,  -1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
      1.0, -1.0, 1.0,  -1.0, -1.0, 1.0,  1.0, 1.0,  1.0,  -1.0, 1.0,  1.0};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(ScaleTest, HandlesZeroInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateScaleMatrix(0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(MoveXTest, HandlePositiveInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(5.0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      4.5, -0.5, 0.5,  5.5, -0.5, 0.5,  4.5, 0.5,  0.5,  5.5, 0.5,  0.5,
      4.5, 0.5,  -0.5, 5.5, 0.5,  -0.5, 4.5, -0.5, -0.5, 5.5, -0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(MoveXTest, HandlesNegativeInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(-5.0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -5.5, -0.5, 0.5,  -4.5, -0.5, 0.5,  -5.5, 0.5,  0.5,  -4.5, 0.5,  0.5,
      -5.5, 0.5,  -0.5, -4.5, 0.5,  -0.5, -5.5, -0.5, -0.5, -4.5, -0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(MoveXTest, HandlesZeroInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  -0.5, 0.5,  0.5,  0.5, 0.5,  0.5,
      -0.5, 0.5,  -0.5, 0.5, 0.5,  -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(MoveYTest, HandlePositiveInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(0, 5.0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, 4.5, 0.5,  0.5, 4.5, 0.5,  -0.5, 5.5, 0.5,  0.5, 5.5, 0.5,
      -0.5, 5.5, -0.5, 0.5, 5.5, -0.5, -0.5, 4.5, -0.5, 0.5, 4.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(MoveYTest, HandlesNegativeInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(0, -5.0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -5.5, 0.5,  0.5, -5.5, 0.5,  -0.5, -4.5, 0.5,  0.5, -4.5, 0.5,
      -0.5, -4.5, -0.5, 0.5, -4.5, -0.5, -0.5, -5.5, -0.5, 0.5, -5.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(MoveYTest, HandlesZeroInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  -0.5, 0.5,  0.5,  0.5, 0.5,  0.5,
      -0.5, 0.5,  -0.5, 0.5, 0.5,  -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(MoveZTest, HandlePositiveInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(0, 0, 5.0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -0.5, 5.5, 0.5, -0.5, 5.5, -0.5, 0.5,  5.5, 0.5, 0.5,  5.5,
      -0.5, 0.5,  4.5, 0.5, 0.5,  4.5, -0.5, -0.5, 4.5, 0.5, -0.5, 4.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(MoveZTest, HandlesNegativeInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(0, 0, -5.0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -0.5, -4.5, 0.5, -0.5, -4.5, -0.5, 0.5,  -4.5, 0.5, 0.5,  -4.5,
      -0.5, 0.5,  -5.5, 0.5, 0.5,  -5.5, -0.5, -0.5, -5.5, 0.5, -0.5, -5.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(MoveZTest, HandlesZeroInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  -0.5, 0.5,  0.5,  0.5, 0.5,  0.5,
      -0.5, 0.5,  -0.5, 0.5, 0.5,  -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(RotateXTest, HandlePositiveInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(90.0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,
      -0.5, 0.5,  0.5,  0.5, 0.5,  0.5,  -0.5, 0.5,  -0.5, 0.5, 0.5,  -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(RotateXTest, HandlesNegativeInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(-90.0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, 0.5,  0.5,  0.5, 0.5,  0.5,  -0.5, 0.5,  -0.5, 0.5, 0.5,  -0.5,
      -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5,  0.5, -0.5, 0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(RotateXTest, HandlesZeroInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  -0.5, 0.5,  0.5,  0.5, 0.5,  0.5,
      -0.5, 0.5,  -0.5, 0.5, 0.5,  -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(RotateYTest, HandlePositiveInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0, 90.0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      0.5,  -0.5, 0.5, 0.5,  -0.5, -0.5, 0.5,  0.5,  0.5, 0.5,  0.5,  -0.5,
      -0.5, 0.5,  0.5, -0.5, 0.5,  -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(RotateYTest, HandlesNegativeInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0, -90.0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5,  -0.5, -0.5, 0.5,  0.5,
      0.5,  0.5,  -0.5, 0.5,  0.5,  0.5, 0.5,  -0.5, -0.5, 0.5,  -0.5, 0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(RotateYTest, HandlesZeroInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  -0.5, 0.5,  0.5,  0.5, 0.5,  0.5,
      -0.5, 0.5,  -0.5, 0.5, 0.5,  -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(RotateZTest, HandlePositiveInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0, 0, 90.0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      0.5,  -0.5, 0.5,  0.5,  0.5, 0.5,  -0.5, -0.5, 0.5,  -0.5, 0.5, 0.5,
      -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5,  -0.5, -0.5, 0.5,  0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(RotateZTest, HandlesNegativeInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0, 0, -90.0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, 0.5, 0.5,  -0.5, -0.5, 0.5,  0.5,  0.5, 0.5,  0.5,  -0.5, 0.5,
      0.5,  0.5, -0.5, 0.5,  -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(RotateZTest, HandlesZeroInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  std::vector<double> expected_coordinates = {
      -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  -0.5, 0.5,  0.5,  0.5, 0.5,  0.5,
      -0.5, 0.5,  -0.5, 0.5, 0.5,  -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5};
  compare_coordinates(vertices, expected_coordinates);
}

TEST(LoadSceneTest, HandlesCorrectVerticesLines) {
  std::string path = "./tests/objects/Cube.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  std::vector<double> expected_coordinates = {
      0.0, 0.0, 0.0, 0.0, 0.0, 5.0, 0.0, 5.0, 0.0, 0.0, 5.0, 5.0,
      5.0, 0.0, 0.0, 5.0, 0.0, 5.0, 5.0, 5.0, 0.0, 5.0, 5.0, 5.0};
  compare_coordinates(loaded_scene.GetFigures()[0].GetVertices(),
                      expected_coordinates);
}

TEST(LoadSceneTest, HandlesVerticesLinesWithIncorectDecimalDelimeter) {
  std::string path = "./tests/objects/CubeIncorrectVertices1.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesVerticesLinesWithTooMuchCoordinates) {
  std::string path = "./tests/objects/CubeIncorrectVertices2.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesVerticesLinesWithIncorrectCoordinatesValue_1) {
  std::string path = "./tests/objects/CubeIncorrectVertices3.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesVerticesLinesWithIncorrectCoordinatesValue_2) {
  std::string path = "./tests/objects/CubeIncorrectVertices4.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesVerticesLinesWithIncorrectCoordinatesValue_3) {
  std::string path = "./tests/objects/CubeIncorrectVertices5.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesVerticesLinesWithIncorectCoordinatesDelimeter) {
  std::string path = "./tests/objects/CubeIncorrectVertices6.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesEmptyVerticesLines) {
  std::string path = "./tests/objects/CubeIncorrectVertices7.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesVerticesLinesWithTooFewCoordinates) {
  std::string path = "./tests/objects/CubeIncorrectVertices8.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesCorrectFaceLinesWithPositiveIndices) {
  std::string path = "./tests/objects/Cube.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  std::vector<unsigned int> expected_indices = {
      0, 6, 6, 4, 0, 2, 2, 6, 0, 3, 3, 2, 0, 1, 1, 3, 2, 7, 7, 6, 2, 3, 3, 7,
      4, 6, 6, 7, 4, 7, 7, 5, 0, 4, 4, 5, 0, 5, 5, 1, 1, 5, 5, 7, 1, 7, 7, 3};
  compare_indices(loaded_scene.GetFigures()[0].GetEdges(), expected_indices);
}

TEST(LoadSceneTest, HandlesCorrectFaceLinesWithNegativeIndices) {
  std::string path = "./tests/objects/Cube.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  std::vector<unsigned int> expected_indices = {
      0, 6, 6, 4, 0, 2, 2, 6, 0, 3, 3, 2, 0, 1, 1, 3, 2, 7, 7, 6, 2, 3, 3, 7,
      4, 6, 6, 7, 4, 7, 7, 5, 0, 4, 4, 5, 0, 5, 5, 1, 1, 5, 5, 7, 1, 7, 7, 3};
  compare_indices(loaded_scene.GetFigures()[0].GetEdges(), expected_indices);
}

TEST(LoadSceneTest, HandlesEmptyFaceLines) {
  std::string path = "./tests/objects/CubeIncorrectFacets1.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesFaceLinesWithIncorrectElement_1) {
  std::string path = "./tests/objects/CubeIncorrectFacets2.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesFaceLinesWithIncorrectElement_2) {
  std::string path = "./tests/objects/CubeIncorrectFacets3.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesFaceLinesWithIncorrectElement_3) {
  std::string path = "./tests/objects/CubeIncorrectFacets7.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesFaceLinesWithTooMuchIndicesInElement) {
  std::string path = "./tests/objects/CubeIncorrectFacets4.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesFaceLinesWithTooFewIndicesInElement) {
  std::string path = "./tests/objects/CubeIncorrectFacets5.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesFaceLinesWithTooFewElements) {
  std::string path = "./tests/objects/CubeIncorrectFacets6.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesFaceLinesWithTooHighIndexValue_1) {
  std::string path = "./tests/objects/CubeIncorrectFacets8.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesFaceLinesWithTooHighIndexValue_2) {
  std::string path = "./tests/objects/CubeIncorrectFacets9.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(LoadSceneTest, HandlesFileWithoutVerticesAndFacets) {
  std::string path = "./tests/objects/CubeWithoutVerticesAndFacets.obj";
  s21::Scene loaded_scene = s21::FileReader::GetInstance().ReadScene(path);
  EXPECT_EQ(loaded_scene.GetFigures().size(), 0);
}

TEST(ScaleTest_1, HandleInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateScaleMatrix(2.0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();

  s21::Point3D pos0 = vertices[0].GetPosition();
  EXPECT_EQ(pos0.x, -1);
  EXPECT_EQ(pos0.y, -1);
  EXPECT_EQ(pos0.z, 1);

  s21::Point3D pos4 = vertices[4].GetPosition();
  EXPECT_EQ(pos4.x, -1);
  EXPECT_EQ(pos4.y, 1);
  EXPECT_EQ(pos4.z, -1);

  s21::Point3D pos7 = vertices[7].GetPosition();
  EXPECT_EQ(pos7.x, 1);
  EXPECT_EQ(pos7.y, -1);
  EXPECT_EQ(pos7.z, -1);
}

TEST(MoveTest_1, HandleInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(5.0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();

  s21::Point3D pos0 = vertices[0].GetPosition();
  EXPECT_EQ(pos0.x, 4.5);
  EXPECT_EQ(pos0.y, -0.5);
  EXPECT_EQ(pos0.z, 0.5);

  s21::Point3D pos4 = vertices[4].GetPosition();
  EXPECT_EQ(pos4.x, 4.5);
  EXPECT_EQ(pos4.y, 0.5);
  EXPECT_EQ(pos4.z, -0.5);

  s21::Point3D pos7 = vertices[7].GetPosition();
  EXPECT_EQ(pos7.x, 5.5);
  EXPECT_EQ(pos7.y, -0.5);
  EXPECT_EQ(pos7.z, -0.5);
}

TEST(MoveTest_2, HandleInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(0, -3.5, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();

  s21::Point3D pos0 = vertices[0].GetPosition();
  EXPECT_EQ(pos0.x, -0.5);
  EXPECT_EQ(pos0.y, -4.0);
  EXPECT_EQ(pos0.z, 0.5);

  s21::Point3D pos4 = vertices[4].GetPosition();
  EXPECT_EQ(pos4.x, -0.5);
  EXPECT_EQ(pos4.y, -3.0);
  EXPECT_EQ(pos4.z, -0.5);

  s21::Point3D pos7 = vertices[7].GetPosition();
  EXPECT_EQ(pos7.x, 0.5);
  EXPECT_EQ(pos7.y, -4.0);
  EXPECT_EQ(pos7.z, -0.5);
}

TEST(MoveTest_3, HandleInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateMoveMatrix(0, 0, 2.0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();
  s21::Point3D pos0 = vertices[0].GetPosition();
  EXPECT_EQ(pos0.x, -0.5);
  EXPECT_EQ(pos0.y, -0.5);
  EXPECT_EQ(pos0.z, 2.5);

  s21::Point3D pos4 = vertices[4].GetPosition();
  EXPECT_EQ(pos4.x, -0.5);
  EXPECT_EQ(pos4.y, 0.5);
  EXPECT_EQ(pos4.z, 1.5);

  s21::Point3D pos7 = vertices[7].GetPosition();
  EXPECT_EQ(pos7.x, 0.5);
  EXPECT_EQ(pos7.y, -0.5);
  EXPECT_EQ(pos7.z, 1.5);
}

TEST(RotateTest_1, HandleInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(60.0, 0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();

  s21::Point3D pos0 = vertices[0].GetPosition();
  EXPECT_NEAR(pos0.x, -0.5, kEps);
  EXPECT_NEAR(pos0.y, -0.683013, kEps);
  EXPECT_NEAR(pos0.z, -0.183013, kEps);

  s21::Point3D pos4 = vertices[4].GetPosition();
  EXPECT_NEAR(pos4.x, -0.5, kEps);
  EXPECT_NEAR(pos4.y, 0.683013, kEps);
  EXPECT_NEAR(pos4.z, 0.183013, kEps);

  s21::Point3D pos7 = vertices[7].GetPosition();
  EXPECT_NEAR(pos7.x, 0.5, kEps);
  EXPECT_NEAR(pos7.y, 0.183013, kEps);
  EXPECT_NEAR(pos7.z, -0.683013, kEps);
}

TEST(RotateTest_2, HandleInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0, -75.0, 0);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();

  s21::Point3D pos0 = vertices[0].GetPosition();
  EXPECT_NEAR(pos0.x, -0.612372, kEps);
  EXPECT_NEAR(pos0.y, -0.5, kEps);
  EXPECT_NEAR(pos0.z, -0.353553, kEps);

  s21::Point3D pos4 = vertices[4].GetPosition();
  EXPECT_NEAR(pos4.x, 0.353553, kEps);
  EXPECT_NEAR(pos4.y, 0.5, kEps);
  EXPECT_NEAR(pos4.z, -0.612372, kEps);

  s21::Point3D pos7 = vertices[7].GetPosition();
  EXPECT_NEAR(pos7.x, 0.612372, kEps);
  EXPECT_NEAR(pos7.y, -0.5, kEps);
  EXPECT_NEAR(pos7.z, 0.353553, kEps);
}

TEST(RotateTest_3, HandleInput) {
  s21::Figure cube = CreateCube();
  s21::TransformMatrix matrix =
      s21::TransformMatrixBuilder::CreateRotationMatrix(0, 0, 55);
  cube.Transform(matrix);
  std::vector<s21::Vertex> vertices = cube.GetVertices();

  s21::Point3D pos0 = vertices[0].GetPosition();
  EXPECT_NEAR(pos0.x, 0.122787, kEps);
  EXPECT_NEAR(pos0.y, -0.696364, kEps);
  EXPECT_NEAR(pos0.z, 0.5, kEps);

  s21::Point3D pos4 = vertices[4].GetPosition();
  EXPECT_NEAR(pos4.x, -0.696364, kEps);
  EXPECT_NEAR(pos4.y, -0.122787, kEps);
  EXPECT_NEAR(pos4.z, -0.5, kEps);

  s21::Point3D pos7 = vertices[7].GetPosition();
  EXPECT_NEAR(pos7.x, 0.696364, kEps);
  EXPECT_NEAR(pos7.y, 0.122787, kEps);
  EXPECT_NEAR(pos7.z, -0.5, kEps);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
