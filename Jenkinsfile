pipeline {
    agent any

    environment {
        // Define any necessary environment variables here
        BUILD_DIR = 'build'
        DEPLOY_DIR = 'smart_nutrition_server'
    }

    stages {
        stage('Build') {
            steps {
                script {
                    // Ensure the build directory is clean
                    sh 'rm -rf ${BUILD_DIR}'
                    
                    // Create and navigate to the build directory
                    sh 'mkdir -p ${BUILD_DIR}'
                    dir("${BUILD_DIR}") {
                        // Run CMake to configure the build
                        sh 'cmake ..'
                        
                        // Build the project
                        sh 'make -j$(nproc)'  // Use all available cores for faster build
                    }
                }
            }
        }

        stage('Run') {
            steps {
                script {
                    // Grand write permissions to the data directory
                    sh 'chmod -R a+w data' 

                    // Terminate any existing instances of the application
                    sh 'lsof -t -i :4000 | grep -v "^$" | xargs -r sudo kill -9'

                    // Start the application in the background
                    sh "screen -dmS smartnutrition ./${BUILD_DIR}/SmartNutritionServer"
                }
            }
        }
    }

    post {
        success {
            echo 'Build and deployment completed successfully.'
        }

        failure {
            echo 'Build or deployment failed.'
        }
    }
}
