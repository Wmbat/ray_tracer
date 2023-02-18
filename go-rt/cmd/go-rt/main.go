package main

import (
	"github.com/wmbat/ray_tracer/internal/maths"
	"github.com/wmbat/ray_tracer/internal/render"
	"github.com/wmbat/ray_tracer/internal/world"
	"github.com/wmbat/ray_tracer/internal/world/entt"
)

const aspectRatio float64 = 16.0 / 9.0
const imageWidth int64 = 720
const imageHeight int64 = int64((float64(imageWidth) / aspectRatio))

func main() {
	viewport := maths.Size2f{Width: aspectRatio * 2.0, Height: 2.0}
	camera := world.NewCamera(maths.Point3{X: 0, Y: 0, Z: 0}, viewport, 1.0)

	sceneName := "Test Scene"

	mainScene := world.NewScene(sceneName)
	mainScene.SetEnvironmentColour(render.Colour{Red: 135 / 256.0, Green: 206 / 256.0, Blue: 235 / 256.0})
	mainScene.AddEntity(entt.Sphere{Origin: maths.Point3{X: 0, Y: 0, Z: 1}, Radius: 0.5})
	mainScene.AddEntity(entt.Sphere{Origin: maths.Point3{X: 0, Y: -100.5, Z: 1}, Radius: 100})

	image := mainScene.Render(camera, world.ImageRenderConfig{
		ImageSize: maths.Size2i{Width: imageWidth, Height: imageHeight},
		SampleCount: 100,
		BounceDepth: 50,
	})

	image.SaveAsPPM(sceneName)
}
