import static com.kms.katalon.core.checkpoint.CheckpointFactory.findCheckpoint
import static com.kms.katalon.core.testcase.TestCaseFactory.findTestCase
import static com.kms.katalon.core.testdata.TestDataFactory.findTestData
import static com.kms.katalon.core.testobject.ObjectRepository.findTestObject
import static com.kms.katalon.core.testobject.ObjectRepository.findWindowsObject
import com.kms.katalon.core.checkpoint.Checkpoint as Checkpoint
import com.kms.katalon.core.cucumber.keyword.CucumberBuiltinKeywords as CucumberKW
import com.kms.katalon.core.mobile.keyword.MobileBuiltInKeywords as Mobile
import com.kms.katalon.core.model.FailureHandling as FailureHandling
import com.kms.katalon.core.testcase.TestCase as TestCase
import com.kms.katalon.core.testdata.TestData as TestData
import com.kms.katalon.core.testobject.TestObject as TestObject
import com.kms.katalon.core.webservice.keyword.WSBuiltInKeywords as WS
import com.kms.katalon.core.webui.keyword.WebUiBuiltInKeywords as WebUI
import com.kms.katalon.core.windows.keyword.WindowsBuiltinKeywords as Windows
import internal.GlobalVariable as GlobalVariable
import org.openqa.selenium.Keys as Keys

WebUI.openBrowser('')

WebUI.navigateToUrl('http://circus.qamania.org/login/')

WebUI.setText(findTestObject('Page_Circus/input_Error text_username'), 'mkushka')

WebUI.setEncryptedText(findTestObject('Page_Circus/input_Error text_password'), 'qpjlKODgGOE=')

WebUI.doubleClick(findTestObject('Page_Circus/input_Keyword_keyword'))

WebUI.setText(findTestObject('Page_Circus/input_Keyword_keyword'), 'elephants')

WebUI.click(findTestObject('Object Repository/Page_Circus/input_Keyword_defBtn'))

WebUI.setText(findTestObject('Page_Circus/input__105'), '2')

WebUI.click(findTestObject('Page_Circus/button_Book'))

WebUI.click(findTestObject('Page_Circus/a_cart'))

WebUI.click(findTestObject('Page_Circus/a_X'))

WebUI.click(findTestObject('Page_Circus/a_X'))

WebUI.closeBrowser()

