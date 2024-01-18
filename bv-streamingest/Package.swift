// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "bv-streamingest",
    platforms: [
        .iOS(.v14)
    ],
    products: [
        // Products define the executables and libraries a package produces, making them visible to other packages.
        .library(
            name: "bv-streamingest",
            targets: ["bv-streamingest", "HaishinKit", "Logboard"]),
    ],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .binaryTarget(
            name: "bv-streamingest",
            path: "Sources/Frameworks/BVStreamIngest.xcframework"
        ),
        .binaryTarget(
            name: "HaishinKit",
            path: "Sources/Frameworks/HaishinKit.xcframework"
        ),
        .binaryTarget(
            name: "Logboard",
            path: "Sources/Frameworks/Logboard.xcframework"
        ),
    ]
)
